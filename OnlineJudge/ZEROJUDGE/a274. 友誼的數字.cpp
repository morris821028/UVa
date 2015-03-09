#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cmp(const void *i, const void *j) {
	return *(long long *)i - *(long long *)j;
}
long long A[11], Way[11];
int flag, Used[11], N;
void DFS(int idx, int n) {
	int i;
	long long x, y;
	if(n == 0)	{
		for(i = 0; i < idx; i++)
			printf("%lld ", Way[i]);
		puts("");
		flag = 1;return;
	}	
	if(idx >= 2)	x = Way[idx-1]+Way[idx-2], y = Way[idx-1]*Way[idx-2];
	for(i = 0; i < N; i++) {
		if(!Used[i]) {
			if(idx < 2 || (idx >= 2 && (x%A[i] == 0 || y%A[i] == 0))) {
				Used[i] = 1;
				Way[idx] = A[i];
				DFS(idx+1, n-1);
				Used[i] = 0;
			}
			if(flag)	return;
		}
	}
}
int main() {
	int i, j;
	while(scanf("%d", &N) == 1) {
		for(i = 0; i < N; i++)
			scanf("%lld", &A[i]);
		qsort(A, N, sizeof(long long), cmp);
		memset(Used, 0, sizeof(Used));
		flag = 0, DFS(0, N);
		if(!flag)
			puts("No");
	}
	return 0;
}
