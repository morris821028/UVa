#include "snake.h"

int snake(int *ptr, int *row, int *col) {
	int n = 1;
	*row = 1, *col = -1;
	for (int i = 1; ptr[i]; i++) {
		if (ptr[i] != ptr[i-1]+1) {
			*col = i;
			break;
		}
	}
	for (int i = 1; ptr[i]; i++, n++);
	if (*col < 0) *col = n;	
	*row = n / *col;
	int *A = ptr, ok = 1;
	for (int i = 0, pos = 0; i < *row; i++) {
		if (i%2 == 0) {
			for (int j = 0; j < *col; j++) {
				ok &= *A == pos+j, A++;
				if (!ok) {
					*row = i, *col = j;
					return 0;
				}
			}
		} else {
			for (int j = *col - 1; j >= 0; j--) {
				ok &= *A == pos+j, A++;
				if (!ok) {
					*row = i, *col = j;
					return 0;
				}
			}
		}
		pos += *col;
	}
	return ok;
}
