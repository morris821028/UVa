#include <stdio.h> 
#include <algorithm>
#include <string.h>
using namespace std;
int A[105], N, M;
void dfs(int d) {
	if(d == N)	return;
	dfs(d+1);
	printf("Move %d from B%d to B%d\n", d+1, 1 + !A[d], 1 + A[d]);
	A[d] = !A[d];
	dfs(d+1);
}
int main() {
	int testcase, x;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &M);
		memset(A, 0, sizeof(A));
		for(int i = 0; i < M; i++)
			scanf("%d", &x), A[--x] = 1;
		dfs(0);
		puts("");
	}
	return 0;
}
