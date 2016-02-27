#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <omp.h>

#define MAXL (50000>>5)+1
#define BLOCK (1<<20)
#define MAXN (BLOCK>>5)+1
#define GET1(x) (mark1[(x)>>5]>>((x)&31)&1)
#define SET1(x) (mark1[(x)>>5] |= 1<<((x)&31))
#define GET2(x) (mark2[(x)>>5]>>((x)&31)&1)
#define SET2(x) (mark2[(x)>>5] |= 1<<((x)&31))
int mark1[MAXL];
int P[5500], Pt = 0;
void sieve() {
    register int i, j, k;
    SET1(1);
    int n = 50000;
    for (i = 2; i <= n; i++) {
        if (!GET1(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET1(j);
            P[Pt++] = i;
        }
    }
}

int isPrime(int x) {
	int sq = (int) sqrt(x);
	for (int i = 0; i < Pt && P[i] <= sq; i++)
		if (x % P[i] == 0)	return 0;
	return 1;
}
long long min(long long x, long long y) {
	return x < y ? x : y;
}
int main() {
    sieve();
    int l, r;
    int cases = 0;
    while (scanf("%d %d", &l, &r) == 2) {
    	int ret = 0;
    	assert(l >= 1 && l <= r);
    	for (long long i = l; i <= r; i ++)
    		ret += isPrime(i);
		printf("%d\n", ret);
	}
    return 0;
}
