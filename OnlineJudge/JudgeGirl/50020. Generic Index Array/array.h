#ifndef _ARRAY_H
#define _ARRAY_H

typedef struct {
	int val, has;
} ELE;
typedef struct {
	ELE dat[2048];
	int l, r;
} ARRAY;

void init(ARRAY *a,  int left, int right);
int set(ARRAY *a, int index, int value);
int get(ARRAY *a, int index);
void print(ARRAY *a);
void sort(ARRAY *a);

#endif
