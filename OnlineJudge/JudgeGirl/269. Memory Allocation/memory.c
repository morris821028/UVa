#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node* newNode(int l, int r) {
	Node *p = (Node *) malloc(sizeof(Node));
	p->l = l, p->r = r, p->next = NULL;
	return p;
}
static void mergeMemory(Memory *mem) {
	Node *p = mem->head->next, *q = mem->head;
	for (; p != NULL && p->next != NULL; ) {
		if (p->r+1 == p->next->l) {
			p->next->l = p->l;
			q->next = p->next;
			Node *t = p;
			p = p->next;
			free(t);
		} else {
			q = p, p = p->next;
		}
	}
}
void initMemory(Memory *mem, int len) {
	mem->size = len;
	mem->head = newNode(-1, -1);
	mem->head->next = newNode(0, len-1);
}
void printMemory(Memory *mem) {
	puts("==========");
	for (Node *p = mem->head->next; p; p = p->next) {
		printf("start %d, length %d\n", p->l, p->r - p->l + 1);
	}
}
void allocateMemory(Memory *mem, int start, int len) {
	Node *p = mem->head->next, *q = mem->head;
	for (; p != NULL; q = p, p = p->next) {
		if (p->l <= start && start <= p->r) {
			if (p->l == start) {
				p->l += len;
				if (p->l > p->r) {
					q->next = p->next;
					free(p);
				}
			} else {
				Node *t = newNode(p->l, start-1);
				p->l = start + len;
				if (p->l > p->r) {
					q->next = t, t->next = p->next;
					free(p);
				} else {
					q->next = t, t->next = p;
				}
			}
			return ;
		}
	}
}
void freeMemory(Memory *mem, int start, int len) {
	if (len == 0)
		return ;
	Node *p = mem->head->next, *q = mem->head;
	for (; p != NULL; q = p, p = p->next) {
		if (p->l > start+len-1) {
			Node *t = newNode(start, start+len-1);
			t->next = p, q->next = t;
			mergeMemory(mem);
			return ;
		}
	}
	q->next = newNode(start, start+len-1);
	mergeMemory(mem);
}
