#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
#define maxL (50000>>5)+1
#define MAXN (2000000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
#define GET2(x) (mark2[x>>5]>>(x&31)&1)
#define SET2(x) (mark2[x>>5] |= 1<<(x&31))
int mark[maxL], mark2[MAXN];
int P[5500], Pt = 0;
void sieve() {
	register int i, j, k;
	SET(1);
	int n = 50000;
	for(i = 2; i <= n; i++) {
			if(!GET(i)) {
			for (k = n/i, j = i*k; k >= i; k--, j -= i)
				SET(j);
			P[Pt++] = i;
		}
	}
}

int local_sieve(int a, int b, int k, int s) {	
	int sqr = sqrt(b), gap = b - a;
	memset(mark2, 0, ((gap>>5) + 1) * 4);
	
	for (int i = 0; i < Pt && P[i] <= sqr; i++) {
		int p = P[i], base = a / p * p;
		while (base <= p)	base += p;
		for (int j = base; j <= b; j += p)
			SET2(j - a);
	}
	if (a == 1)	SET2(0);
	queue<int> Q;
	int ret = 0;
	for (int i = 0; i <= gap; i++) {
		if (!GET2(i)) {
			if (Q.size() == k - 1) {
				if (k == 0)
					ret += s == 0;
				else if ((a + i) - Q.front() == s)
					ret++;
			}
			Q.push(a + i);
			while (Q.size() >= k)	Q.pop();
		}
	}
	return ret;
}
int main() {
	sieve();
	
	int testcase;
	int a, b, k, s;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d %d", &a, &b, &k, &s);
		printf("%d\n", local_sieve(a, b, k, s));
	}
	return 0;
}
