#include "card.h"

void shuffle(int *deck[]) {
	int n = 0;
	for (int i = 0; deck[i]; i++)
		n++;
	int A[10000] = {}, pos = 0, i;
	for (i = 0; pos < n && i < n; i++, pos += 2)
		A[pos] = *(deck[i]);
	pos = 1;
	for (; pos < n && i < n; i++, pos += 2)
		A[pos] = *(deck[i]);
	for (int i = 0; i < n; i++)
		*(deck[i]) = A[i];
}
void print(int *deck[]) {
	for (int i = 0; deck[i]; i++) {
		printf("%d", *(deck[i]));
		if (deck[i+1])	printf(" ");
		else			puts("");
	}
}
