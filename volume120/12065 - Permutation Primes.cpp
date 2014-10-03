#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>
using namespace std;
#define maxL (1111111>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[100000], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1111111;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
int check(int n) {
	static char buf1[25], buf2[25];
	sprintf(buf1, "%d", n);
	int p, q, m = strlen(buf1);
	sort(buf1, buf1 + m);
	do {
		p = 0;
		for (int i = 0; i < m; i++)
			p = p * 10 + buf1[i] - '0';
		if (p == n)	continue;
		q = abs(n - p);
		if (q%9 == 0 && q/9 < 1111111) {
			if (!GET(q/9))
				return 1;
		}
	} while (next_permutation(buf1, buf1 + m));
	return 0;
}
int main() {
	sieve();
	int testcase, cases = 0, l, r;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &l, &r);
		if (r < l)
			swap(l, r);
		int ret = 0;
		for (int i = l; i <= r; i++) {
			if (check(i))
				ret++;
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
