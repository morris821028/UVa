#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, M, K;
	while (scanf("%d %d %d", &N, &M, &K) == 3) {
		pair<int, int> A[505];
		int has[505] = {}, x;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				scanf("%d", &x);
				A[x] = make_pair(i, j), has[x] = 1;
			}
		}
		
		int px = -1, py = -1;
		int ret = 0, sum = 0, time = 0;
		for (int i = 500; i >= 1; i--) {
			if (has[i] == 0)
				continue;
			int x = A[i].first, y = A[i].second;
			if (px == -1)
				time += x;
			else
				time += abs(px - x) + abs(py - y);
			sum += i, time++;
			if (time + x <= K)
				ret = max(ret, sum);
			px = x, py = y;
		}
		printf("%d\n", ret);
	}
	return 0;
}
