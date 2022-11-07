#include "UIP.h"
#define SAFE_HANDLE(a) if(a){CloseHandle(a);}

int main() {

	ring_buffer* ring_in = (ring_buffer*)malloc(sizeof(ring_buffer));
	if (ring_in == NULL) {
		printf("Not enough memory.");
		return -1;
	}

	ring_buffer* ring_out = (ring_buffer*)malloc(sizeof(ring_buffer));
	if (ring_out == NULL) {
		printf("Not enough memory.");
		return -2;
	}

	buffer_pointers* buff_points = (buffer_pointers*)malloc(sizeof(buffer_pointers));
	if (buff_points == NULL) {
		printf("Not enough memory.");
		return -3;
	}
	buff_points->in_buffer = ring_in;
	buff_points->out_buffer = ring_out;


	init_ring_buffer(ring_in);
	init_ring_buffer(ring_out);
	
	// Producer // Consumer // Process
	HANDLE prod_h = NULL, cons_h = NULL, proc_h = NULL;
	DWORD prod_id, cons_id, proc_id;

	Empty1 = CreateSemaphore(0, RING_SIZE, RING_SIZE, NULL);
	Full1 = CreateSemaphore(0, 0, RING_SIZE, NULL);
	Exit = CreateSemaphore(0, 0, 3, NULL);

	Empty2 = CreateSemaphore(0, RING_SIZE, RING_SIZE, NULL);
	Full2 = CreateSemaphore(0, 0, RING_SIZE, NULL);

	
	if (Full1 && Empty1 && Exit) {

		prod_h = CreateThread(NULL, 0, &producer_func, ring_in, 0, &prod_id);
		proc_h = CreateThread(NULL, 0, &process_func, buff_points, 0, &proc_id);
		cons_h = CreateThread(NULL, 0, &consumer_func, ring_out, 0, &cons_id);

		if (!prod_h || !cons_h || !proc_h) {
			ReleaseSemaphore(Exit, 3, NULL);
		}
		else 
		{
			WaitForSingleObject(prod_h, INFINITE);
			WaitForSingleObject(cons_h, INFINITE);
		}
	}

	SAFE_HANDLE(prod_h);
	SAFE_HANDLE(cons_h);
	SAFE_HANDLE(Empty1);
	SAFE_HANDLE(Full1);
	SAFE_HANDLE(Exit);
	SAFE_HANDLE(Empty2);
	SAFE_HANDLE(Full2);

	free(ring_in);
	DeleteCriticalSection(&buffer1);
	DeleteCriticalSection(&buffer2);

	return 0;
}