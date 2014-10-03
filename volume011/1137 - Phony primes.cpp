#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
#define maxL (50000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
long long P[10000];
int Pt = 0;
void sieve() {
	int mark[maxL];
    register int i, j, k;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

#define MAXN 1048576
int used[MAXN], val[MAXN], fcnt[MAXN];
int main() {
	sieve();
	long long L, R;
	int cases = 0;
	while (scanf("%lld %lld", &L, &R) == 2) {
		if (cases++)	puts("");
		int has = 0;
		for (int i = R - L; i >= 0; i--)
			val[i] = i + L, fcnt[i] = 0;
		for (int i = 0; i < Pt && P[i] * P[i] <= R; i++) {
			int d = P[i], d2 = P[i] * P[i];
			for (long long j = ((L-1)/d2+1) * d2; j <= R; j += d2)
				used[j - L] = cases; // check distinct prime factors
			for (long long j = ((L-1)/d+1) * d; j <= R; j += d) {
				if ((j-1)%(d-1))
					used[j - L] = cases;
				fcnt[j - L]++, val[j - L] /= d; 
			}
		}
		for (int i = 0; i <= R - L; i++)
			fcnt[i] += val[i] != 1;
		for (int i = 0; i <= R - L; i++) {
			if (used[i] != cases && fcnt[i] >= 3) {
				if (val[i] == 1 || (i + L-1)%(val[i]-1) == 0)
					printf("%d\n", i + L), has = 1;
			}
		}
		if (!has)
			puts("none");
	}
	return 0;
}
