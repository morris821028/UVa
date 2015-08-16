#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <set>
#include <algorithm>
using namespace std;

int main() {
	int testcase;
	int N;
	long long A[64], B[64];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%lld", &A[i]);
		for (int i = 0; i < N; i++)
			scanf("%lld", &B[i]);
		if (N == 1) {
			printf("%lld\n", llabs(A[0] - A[0]));
			continue;
		}
		
		int div1 = N/2, div2 = N - N/2;
		long long ret = LONG_LONG_MAX;
		set<long long> S1[64], S2[64];
		for (int i = 0; i < (1<<div1); i++) {
			long long a = 0, b = 0;
			for (int j = 0; j < div1; j++) {
				if ((i>>j)&1)
					a += A[j];
				else
					b += B[j]; 
			}
			S1[__builtin_popcount(i)].insert(a - b);
		}
		for (int i = 0; i < (1<<div2); i++) {
			long long a = 0, b = 0;
			for (int j = 0; j < div2; j++) {
				if ((i>>j)&1)
					a += A[j+div1];
				else
					b += B[j+div1]; 
			}
			S2[__builtin_popcount(i)].insert(a - b);
		}
		set<long long>::iterator it, jt, kt;
		int a, b;
		if (N&1)	a = N/2, b = N - N/2;
		else		a = N/2, b = N/2;
		for (int i = a; i <= b; i++) {
			for (int j = 0; j <= i; j++) {
				for (it = S1[j].begin(); it != S1[j].end(); it++) {
					long long d1 = *it, d2;
					jt = S2[i-j].lower_bound(-d1);
					if (jt != S2[i-j].end()) {
						d2 = *jt;
						ret = min(ret, llabs(d1+d2));
					}
					if (jt != S2[i-j].begin()) {
						jt--;
						d2 = *jt;
						ret = min(ret, llabs(d1+d2));
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2
3
3 5 4
2 7 3
2
2 4
3 5
*/
