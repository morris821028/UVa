#include <stdio.h>

int N, M, K, A[32];
int dfs(int idx, int pick, int sum) {
	if (idx == N)
		return sum <= M && pick >= K;
	return dfs(idx+1, pick, sum) + dfs(idx+1, pick+1, sum+A[idx]);
}
int main() {
	while (scanf("%d %d %d", &K, &N, &M) == 3) {
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		int ret = dfs(0, 0, 0);
		printf("%d\n", ret);
	}
	return 0;
}

