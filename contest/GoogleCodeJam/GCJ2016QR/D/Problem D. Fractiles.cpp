#include <bits/stdc++.h>
using namespace std;

long long mpow(long long x, long long y) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = ret * x;
		y >>= 1, x = x*x;
	}
	return ret;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long K, C, S;
		scanf("%lld %lld %lld", &K, &C, &S);
		printf("Case #%d:", ++cases);
		
		int pos = 0;
		vector<unsigned long long> A;
//		puts("");
		for (int i = 0; i < ceil(1.f*K/C); i++) {
			int item = min(C, K - pos);
			unsigned long long x = 0;
			for (int j = C-1, k = 0; j >= 0 && k < item; j--, k++) {
//				printf("%d K^%d + ", pos + k, j);
				x += (pos + k) * mpow(K, j);
			}
			A.push_back(x);
//			puts("");
			pos += C;
			if (pos > K)	pos = K;
		}
		if (A.size() > S)
			puts(" IMPOSSIBLE");
		else {
			for (int i = 0; i < A.size(); i++)
				printf(" %llu", A[i]+1);
			puts("");
		}
	}
	return 0;
}
/*
5
4 4 5
*/

