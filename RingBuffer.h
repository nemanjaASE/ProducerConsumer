#ifndef RING_BUFFER_HEADER
#define RING_BUFFER_HEADER

#endif

#define RING_SIZE 256

typedef struct ring_buffer {
	char buffer[RING_SIZE];
	unsigned int push_idx;
	unsigned int pop_idx;
};

void init_ring_buffer(ring_buffer* ring_b);

void push_char(ring_buffer* ring_b, char ch);

char pop_char(ring_buffer* ring_b);
