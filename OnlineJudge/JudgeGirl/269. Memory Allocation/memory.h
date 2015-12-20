#ifndef _MEMORY_H
#define _MEMORY_H

typedef struct Node {
	int l, r;
	struct Node *next;
} Node;
typedef struct Memory {
	int size;
	Node *head;
} Memory;

void initMemory(Memory *memory, int length);
void printMemory(Memory *memory);
void allocateMemory(Memory *memory, int start, int length);
void freeMemory(Memory *memory, int start, int length);

#endif
