#ifndef UIP_INCLUDE
#define UIP_INCLUDE

#endif

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "RingBuffer.h"


extern HANDLE Empty1, Full1, Exit;
extern HANDLE Empty2, Full2;
extern CRITICAL_SECTION buffer1, buffer2;

typedef struct buffer_pointers {
	ring_buffer* in_buffer;
	ring_buffer* out_buffer;
};

DWORD WINAPI producer_func(LPVOID param);

DWORD WINAPI process_func(LPVOID param);

DWORD WINAPI consumer_func(LPVOID param);

