#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		long long N, M;
		scanf("%lld %lld", &N, &M);
		long long S = N + M, ret;
		ret = (S*(S+1)/2) + N + 1;
		printf("%lld\n", ret);
	}
	return 0;
}

