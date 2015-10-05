#include "evaluate_f.h"

int evaluate_f(int *iptr[], int n, int *index) {
	int r = -1, mx = 0;
	for (int i = 0; i < n; i++) {
		int f = 4 * iptr[i][0] - 6 * iptr[i][1];
		if (r == -1 || f > mx)
			r = i, mx = f;
	}
	*index = r;
	return mx;
}
