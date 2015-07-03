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
    testcase = 10;
	freopen("in.txt", "w+t", stdout);
//    printf("%d\n", testcase);
	while (testcase--) {
        n = 1024, m = 512;
        printf("%d %d\n", n, m);
        vector<string> A;
        for (int i = 0; i < n; i++) {
            string x = "";
            if (i == 0 || rand()%n < n/32) {
                for (int j = 0; j < m; j++)
                    x += (char) (rand()%2 + '0');
                printf("%s\n", x.c_str());
            } else {
                x = A[rand()%i];
                int diff = rand()% (m / 32);
                for (int j = 0; j < m; j++) {
                    if (rand()%32 == 0 && diff > 0) {
                        diff--;
                        x[j] = x[j] == '0' ? '1' : '0';
                    }
                }
                printf("%s\n", x.c_str());
            }
            A.push_back(x);
        }
        if (testcase)
        	puts("");
	}
	return 0;
}
