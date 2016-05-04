#include <bits/stdc++.h>
using namespace std;
#define MAXL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int phi[1048576];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000000;
    phi[1] = 0;
    for (i = 2; i <= n; i++)
    	phi[i] = i;
    for (i = 2; i <= n; i++) {
        if(!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            for (j = i; j <= n; j += i)
            	phi[j] = phi[j]/i * (i-1);
        }
    }
}
long long ret[1048576];
int main() {
	sieve();
	for (int i = 1; i <= 1000000; i++)
		ret[i] = ret[i-1] + phi[i];
	int n;
	while (scanf("%d", &n) == 1 && n)
		printf("%lld\n", ret[n]);
	return 0;
}

