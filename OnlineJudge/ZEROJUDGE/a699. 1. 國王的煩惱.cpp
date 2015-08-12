#include <bits/stdc++.h>
using namespace std;

#define MAXL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
void sieve() {
    register int i, j, k;
    SET(1), SET(0);
    int n = 671064;
    for (i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}

int main() {
	sieve();
	int n;
	while (scanf("%d", &n) == 1)
		puts(GET(n) ? "It's not a prime!!!" : "It's a prime!!!");
	return 0;
}
