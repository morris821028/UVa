#include <stdio.h>
#include <stdlib.h>
#define LL long long
#define maxL (1300000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
using namespace std;
int mark[maxL];
int anaP[30], at = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1300000;
    for(i = 2; i < n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}
main() {
    sieve();
    int n;
    while(scanf("%d", &n) == 1 && n) {
    	int ret = 0;
    	for(int i = n; GET(i); i++, ret++);
    	for(int i = n; GET(i) && i > 0; i--, ret++);
    	printf("%d\n", ret);
    }
    return 0;
}

