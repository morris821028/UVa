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
 
int local_sieve(int a, int b) {
    int sqr = (int) sqrt(b), gap = b - a;
    int *mark2 = (int *) calloc(MAXN, sizeof(int));
 
    for (int i = 0; i < Pt && P[i] <= sqr; i++) {
        unsigned p = P[i], base = a / p * p;
        while (base < a)    base += p;
        if (base == p)    base += p;
        for (unsigned j = base; j <= b; j += p)
            SET2(j - a);
    }
    if (a == 1)    SET2(0);
    int ret = 0;
    for (int i = 0; i <= gap; i++) {
        if (!GET2(i))
            ret++;
    }
    free(mark2);
    return ret;
}
long long min(long long x, long long y) {
    return x < y ? x : y;
}
int main() {
    sieve();
    int l, r;
    while (scanf("%d %d", &l, &r) == 2) {
        int ret = 0;
        assert(l >= 1 && l <= r);
        #pragma omp parallel for schedule(dynamic) reduction(+: ret)
        for (long long i = l; i <= r; i += BLOCK)
            ret += local_sieve(i, min(i+BLOCK-1, r));
        printf("%d\n", ret);
    }
    return 0;
}
