#include <bits/stdc++.h>
using namespace std;

int main() {
	int N;
	while (scanf("%d", &N) == 1 && N) {
		vector<pair<int, int>> A;
		int L, R;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &L, &R);
			A.push_back(make_pair(L, R));
		}
		sort(A.begin(), A.end());
		
		int ret = 0;
		int PQ = INT_MAX;
		for (int i = 0; i < N; i++) {
			int line_x = A[i].first;
			if (PQ != INT_MAX && PQ <= line_x) {
				ret++;
				PQ = INT_MAX;
			}
			PQ = min(PQ, A[i].second);
		}
		if (PQ != INT_MAX)
			ret++;
		printf("%d\n", ret);
	}
	return 0;
}

