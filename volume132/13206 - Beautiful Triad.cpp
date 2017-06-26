#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int64_t N, K;
		scanf("%lld %lld", &N, &K);
		N++;
		int64_t ret = 0;
		// 3 different number: (N-k) (k-1) 3!
		for (int k = 2; N-k > 0 && k <= K; k++)
			ret += (N-k)*(k-1)*6;
		// 2 different number: (N-k) * 6
		for (int k = 1; N-k > 0 && k <= K; k++)
			ret += (N-k)*6;
		ret += N;
		printf("%lld\n", ret);
	}
	return 0;
}
/*
5
0  0
1  0
1  1
2  1
2000000000  0
*/
