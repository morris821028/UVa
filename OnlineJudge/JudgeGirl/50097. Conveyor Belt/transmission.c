#include "transmission.h"
#include <stdint.h>
#include <string.h>
#define MAXN (1<<20)
void transmission(long long int A[], int N, int T) {
	static int64_t tmp[MAXN];
	uint64_t p = (T>>6)%N, q = T&63, r = 64-(T&63);
	uint64_t *a = A+p, *b = A+p+1, *end = A+N;
	if (r >= 64) {
		memcpy(tmp, A, sizeof(A[0])*p);
		memmove(A, A+p, sizeof(A[0])*(N-p));
		memcpy(A+(N-p), tmp, sizeof(A[0])*p);
		return;
	}
	for (int i = 0; i < N; i++, a++, b++) {
		if (a == end)	a = A;
		if (b == end)	b = A;
		tmp[i] = ((*a)<<q) | ((*b)>>r);
	}
	memcpy(A, tmp, sizeof(A[0])*N);
}
