#include "UIP.h"

#define MAX_SEM 2

HANDLE Empty1, Full1, Exit;
HANDLE Empty2, Full2;

CRITICAL_SECTION buffer1, buffer2;

DWORD WINAPI producer_func(LPVOID param) {
	ring_buffer* ring_b = (ring_buffer*)param;
	InitializeCriticalSection(&buffer1);
	HANDLE semaphore[MAX_SEM] = { Exit, Empty1};

	while (WaitForMultipleObjects(MAX_SEM, semaphore, false, INFINITE) == WAIT_OBJECT_0 + 1) {
		printf("[PRODUCER] Enter character: ");
		char ch = getchar();

		if (ch == '1') {
			ReleaseSemaphore(Exit, 3, NULL);
		}

		EnterCriticalSection(&buffer1);
		push_char(ring_b, ch);
		fseek(stdin, 0, SEEK_END);
		LeaveCriticalSection(&buffer1);

		ReleaseSemaphore(Full1, 1, NULL);
		Sleep(2000);
	}

	return 0;
}

DWORD WINAPI process_func(LPVOID param) {
	InitializeCriticalSection(&buffer2);
	HANDLE semaphore1[MAX_SEM] = {Exit, Full1};
	HANDLE semaphore2[MAX_SEM] = { Exit, Empty2 };
	buffer_pointers* pointers = (buffer_pointers*)param;

	ring_buffer* in_buffer = pointers->in_buffer;
	ring_buffer* out_buffer = pointers->out_buffer;

	while (WaitForMultipleObjects(MAX_SEM, semaphore1, false, INFINITE) == WAIT_OBJECT_0 + 1) {
		EnterCriticalSection(&buffer1);
		char ch = pop_char(in_buffer);
		char new_char = ch - 0x20;
		LeaveCriticalSection(&buffer1);

		printf("[PROCCES] Processing is complete.\n");
		ReleaseSemaphore(Empty1, 1, NULL);

		while (WaitForMultipleObjects(MAX_SEM, semaphore2, false, INFINITE) == WAIT_OBJECT_0 + 1) {
			EnterCriticalSection(&buffer2);
			push_char(out_buffer, new_char);
			LeaveCriticalSection(&buffer2);

			printf("[PROCCES] A new char has been pushed.\n");
			ReleaseSemaphore(Full2, 1, NULL);
			break;
		}
	}

	return 0;
}

DWORD WINAPI consumer_func(LPVOID param) {
	ring_buffer* ring_b = (ring_buffer*)param;

	HANDLE semaphore[MAX_SEM] = { Exit, Full2 };
	while (WaitForMultipleObjects(MAX_SEM, semaphore, false, INFINITE) == WAIT_OBJECT_0 + 1) {
		EnterCriticalSection(&buffer2);
		char ch = pop_char(ring_b);
		LeaveCriticalSection(&buffer2);
		printf("[CONSUMER] Loaded character: %c\n", ch);
		ReleaseSemaphore(Empty2, 1, NULL);
	}

	return 0;
}