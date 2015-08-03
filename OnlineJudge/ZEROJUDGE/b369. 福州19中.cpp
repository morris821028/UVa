#include <bits/stdc++.h>
using namespace std;
#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[5500], Pt = 0;
void sieve() {
	register int i, j, k;
	SET(1);
	int n = 30000;
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
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%d!=", n);
		for (int i = 0; i < Pt; i++) {
			int cnt = 0, v = P[i];
			while (v <= n)
				cnt += n / v, v *= P[i];
			if (cnt == 0)
				break;
			printf("%d ", cnt);
		}
		puts("");
	}
	return 0;
}
