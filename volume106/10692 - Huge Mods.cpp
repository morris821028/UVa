#include <stdio.h>
#include <algorithm>
using namespace std;
#define maxL (10000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int phi[10005];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000;
    for(i = 1; i <= n; i++)
        phi[i] = i;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            phi[i] = phi[i]/i*(i-1);
            for(k = n/i, j = i*k; k >= 2; k--, j -= i) {
                SET(j);
                phi[j] = phi[j]/i*(i-1);
            }
        }
    }
}
int mpow(int x, int y, int mod) {
	int ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		x = (x * x)%mod, y >>= 1;
	}		
	return ret;
}
int mmpow(int idx, int A[], int m, int n)  {
	if (idx == n - 1)
		return A[idx]%m;
	int p = mmpow(idx+1, A, phi[m], n) + phi[m];
	return mpow(A[idx], p, m);
}
int main() {
	sieve();
	int n, m, A[32], cases = 0;
	while (scanf ("%d %d", &m, &n) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		printf("Case #%d: %d\n", ++cases, mmpow(0, A, m, n));		
	}
	return 0;
}
