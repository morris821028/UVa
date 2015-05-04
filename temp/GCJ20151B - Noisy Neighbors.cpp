#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int main() {
	int testcase, cases = 0;
	int N, M, K;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &N, &M, &K);
		
		vector<int> B, W;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				int adj = 0;
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k], y = j + dy[k];
					if (x >= 0 && y >= 0 && x < N && y < M)
						adj++;
				}
				if ((i+j) %2 == 0)
					B.push_back(adj), W.push_back(0);
				else
					B.push_back(0), W.push_back(adj);
			}
		}
		
		sort(B.begin(), B.end());
		sort(W.begin(), W.end());
		
		int cost1 = 0, cost2 = 0, ret = -1;
		for (int i = 0; i < K; i++) {
			cost1 += B[i];
			cost2 += W[i];
		}
		ret = min(cost1, cost2);
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
