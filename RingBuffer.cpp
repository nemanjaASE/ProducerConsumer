#include "RingBuffer.h"
#include <stdio.h>


void init_ring_buffer(ring_buffer* ring_b) {
	if (ring_b == NULL) {
		printf("Invalid value.");
		return;
	}

	ring_b->pop_idx = 0;
	ring_b->push_idx = 0;
}

void push_char(ring_buffer* ring_b, char ch) {
	ring_b->buffer[ring_b->push_idx] = ch;
	ring_b->push_idx = (ring_b->push_idx + 1) % RING_SIZE;
}

char pop_char(ring_buffer* ring_b) {
	char element = ring_b->buffer[ring_b->pop_idx];
	ring_b->pop_idx = (ring_b->pop_idx + 1) % RING_SIZE;
	return element;
}