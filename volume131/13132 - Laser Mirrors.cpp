#include <bits/stdc++.h> 
using namespace std;
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))

const int MAXN = 100005;
const int MAXL = (MAXN>>5)+1;
int mark[MAXL];
int P[10000], Pt = 0;
int phi[MAXN];
void sieve_phi() {
    register int i, j, k;
    SET(1);
    int n = 100000;
    for (i = 1; i <= n; i++)
    	phi[i] = i;
    for (i = 2; i <= n; i++) {
		if (!GET(i)) {
            for (j = i+i; j <= n; j += i)
                SET(j), phi[j] = phi[j] / i * (i-1);
            phi[i] = i-1;
            P[Pt++] = i;
        }
    }
}

int main() {
	sieve_phi();
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("%d\n", phi[n]);
	}
	return 0;
}

