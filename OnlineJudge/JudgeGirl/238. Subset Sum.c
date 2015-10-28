#include <stdio.h>
int N, S, A[20], W[1024] = {};
void dfs(int idx, int A[], int sum) {
	if (idx == N) {
		W[sum]++;
		return ;
	}
	dfs(idx+1, A, sum);
	dfs(idx+1, A, sum+A[idx]);
}
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	dfs(0, A, 0);
	while (scanf("%d", &S) == 1)
		printf("%d\n", W[S]);
	return 0;
}
