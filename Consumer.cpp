#include "Consumer.h"
#define MAX_SEM 256

DWORD WINAPI consumer_func(LPVOID param) {
	ring_buffer* ring_b = (ring_buffer*)param;

	HANDLE semaphore[MAX_SEM] = { Full, Exit };
	while (WaitForMultipleObjects(MAX_SEM, semaphore, false, INFINITE) == WAIT_OBJECT_0 + 1) {
		EnterCriticalSection(&buffer);
		char ch = pop_char(ring_b);
		LeaveCriticalSection(&buffer);
		printf("Ucitan je znak: %c", ch);
		ReleaseSemaphore(Empty, 1, NULL);
	}

	return 0;
}
