#include <bits/stdc++.h>
using namespace std;
#define MAXL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[1048576], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000000;
    for(i = 2; i <= n; i++) {
            if(!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

int main() {
	sieve();
	long long N;
	while (scanf("%lld", &N) == 1 && N != 1) {
		int ret = 0;
		for (int i = 0; i < Pt && (long long) P[i] * P[i] <= N; i++) {
			while (N%P[i] == 0) {
				N /= P[i], ret++;
			}
		}
		if (N != 1)	ret++;
		printf("%d\n", ret);
	}
	return 0;
}

