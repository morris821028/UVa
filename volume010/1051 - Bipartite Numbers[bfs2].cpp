// Accepted
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;

struct ELE {
	int m, s, n, t;
	ELE(int a = 0, int b = 0, int c = 0, int d = 0):
		m(a), s(b), n(c), t(d) {}
	bool operator<(const ELE &x) const {
		if(m + n != x.m + x.n)
			return m + n < x.m + x.n;
		if(s != x.s)
			return s < x.s;
		if(m != x.m)
			return s < x.t;
		return t < x.t;
	}
};
#define MAXL 9999
int M1[MAXL];
int M10[MAXL];

int largeN(int N, ELE key) {
	if(key.m + key.n > 5) // > 100000
		return 1;
	int tmp = 0;
	for(int i = 0; i < key.m; i++)
		tmp = tmp * 10 + key.s;
	for(int i = 0; i < key.n; i++)
		tmp = tmp * 10 + key.t;
	return tmp > N;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout);   
	for(int N; scanf("%d", &N) == 1 && N; ) {
		
		M1[0] = 0;
		M10[0] = 1;
		for(int i = 1; i < MAXL; i++) {
			M1[i] = (M1[i-1] * 10 + 1)%N;
			M10[i] = (M10[i-1] * 10)%N;
		}
		
		ELE key(MAXL);
		for(int len = 2; len < MAXL; len++) {
			for(int i = N%10 || len <= 20 ? 1 : len - 20; i < len; i++) {
				for(int p = 1; p < 10; p++) {
					for(int q = 0; q < 10; q++) {
						if(p == q)
							continue;
						long long m = ((long long)M1[i] * M10[len - i] * p + M1[len - i] * q)%N;
						ELE tkey(i, p, len - i, q);
						if(m == 0 && largeN(N, tkey) && tkey < key) {
							key = tkey;
						}
					}
				}
			}
			if(key.m != MAXL)
				break;
		}
		printf("%d: %d %d %d %d\n", N, 
			key.m, key.s, key.n, key.t);
	}
	return 0;
}
/*
190
24822
344
4455
*/
