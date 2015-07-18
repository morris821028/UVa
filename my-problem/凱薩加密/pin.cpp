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
	freopen("in.txt", "w+t", stdout);
//    printf("%d\n", testcase);
	testcase = 10;
	while (testcase--) {
        n = rand()%10 + 1, m = rand()%26;
        char s[1024];
        for (int i = 0; i < n; i++) {
        	s[i] = rand()%26;
        	printf("%c", s[i] + 'A');
        }
        puts("");
        for (int i = 0; i < n; i++) {
        	printf("%c", (s[i] + m)%26 + 'A');
        }
        puts("");
	}
	testcase = 50;
	while (testcase--) {
        n = rand()%50 + 10, m = rand()%26;
        char s[1024];
        for (int i = 0; i < n; i++) {
        	s[i] = rand()%26;
        	printf("%c", s[i] + 'A');
        }
        puts("");
        for (int i = 0; i < n; i++) {
        	printf("%c", (s[i] + m)%26 + 'A');
        }
        puts("");
	}
	testcase = 100;
	while (testcase--) {
        n = rand()%100 + 50, m = rand()%26;
        char s[1024];
        for (int i = 0; i < n; i++) {
        	s[i] = rand()%26;
        	printf("%c", s[i] + 'A');
        }
        puts("");
        for (int i = 0; i < n; i++) {
        	printf("%c", (s[i] + m)%26 + 'A');
        }
        puts("");
	}
	testcase = 100;
	while (testcase--) {
        n = 1000, m = rand()%26;
        char s[1024];
        for (int i = 0; i < n; i++) {
        	s[i] = rand()%26;
        	printf("%c", s[i] + 'A');
        }
        puts("");
        for (int i = 0; i < n; i++) {
        	printf("%c", (s[i] + m)%26 + 'A');
        }
        puts("");
	}
	return 0;
}
