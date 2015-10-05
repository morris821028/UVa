#include "fill_array.h"
void fill_array(int *ptr[], int n) {
	int *begin = ptr[0], *end = ptr[n-1]+1;
	int m = 0;
	for (int *p = begin; p != end; p++)
		*p = -1, m++;
	for (int i = 0; i < n; i++)
		*(ptr[i]) = i;
	int prev = 0, next = 1;
	while (next < m && begin[next] == -1)
		next++;
	for (int *p = begin; p != end; p++) {
		if (*p == -1) {
			*p = begin[prev] + begin[next];
		} else if (begin+next <= p) {
			prev = next, next++;
			while (next < m && begin[next] == -1)
				next++;
		}		
	}
	return ;
}
