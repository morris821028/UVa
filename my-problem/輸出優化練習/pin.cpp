#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
using namespace std;
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[50000], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 30000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        	if (i%4 == 3)
            	P[Pt++] = i;
        }
    }
}

int main() {
	sieve();
	 srand (time(NULL));
	int testcase, n, m, x, y, a, b;
    testcase = 1000;
	freopen("in.txt", "w+t", stdout);
//    printf("%d\n", testcase);
	while (testcase--) {
        m = 2000;
        do {
        	x = rand()%Pt, y = rand()%Pt;
        } while (x == y);
        n = P[x] * P[y];
        printf("%d %d %d\n", rand()%n + 1, n, m);
        
	}
	return 0;
}
