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
	testcase = 10;
	while (testcase--) {
		int n = P[rand()%Pt%10] * P[rand()%Pt%10], a, b;
		do {
			a = rand()%n + 1;
		} while (__gcd(a, n) != 1);
		b = rand()%n + 1;
		printf("%d %d %d\n", a, b, n);
	}
	testcase = 50;
	while (testcase--) {
		int n = P[rand()%Pt%100] * P[rand()%Pt%100], a, b;
		do {
			a = rand()*rand()%n + 1;
		} while (__gcd(a, n) != 1);
		b = rand()%n + 1;
		printf("%d %d %d\n", a, b, n);
	}
	testcase = 100;
	while (testcase--) {
		int n = P[rand()%Pt%500] * P[rand()%Pt%500], a, b;
		do {
			a = rand()*rand()%n + 1;
		} while (__gcd(a, n) != 1);
		b = rand()%n + 1;
		printf("%d %d %d\n", a, b, n);
	}
	testcase = 100;
	while (testcase--) {
		int n = P[rand()%Pt] * P[rand()%Pt], a, b;
		do {
			a = rand()*rand()%n + 1;
		} while (__gcd(a, n) != 1);
		b = rand()%n + 1;
		printf("%d %d %d\n", a, b, n);
	}
	return 0;
}
