#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int W, N, x;
		scanf("%d %d", &W, &N);
		vector<int> A;
		A.push_back(-1);
		for (int i = 0; i < N; i++) {
			scanf("%d", &x);
			if (x >= W)
				A.push_back(i);
		}
		A.push_back(N);
		int ret = 0;
		for (int i = 1; i < A.size()-1; i++) {
			int x = A[min(i+5, (int)A.size()-1)];
			ret = max(ret, x - A[i-1]-1);
		}
		if (A.size() == 2)	ret = N;
		printf("%d\n", ret);
	}
	return 0;
}

