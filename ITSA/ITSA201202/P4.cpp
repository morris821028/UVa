#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define oo 2147483647
int Ans, use[1000], D[1000], A[1000];
int n, tmp[1000], pos[1000], i;
void DFS(int now, int sum, int sumday) {
	if(now == n) {
		if(sum < Ans) {
			int i;
			for(i = 0; i < n; i++)
				tmp[i] = pos[i];
			Ans = sum;
		}
		return ;
	}
	if(sum >= Ans)	return;
	int i;
	for(i = 0; i < n; i++) {
		if(use[i] == 0) {
			use[i] = 1;
			pos[now] = i;
			DFS(now+1, sum+sumday*A[i], sumday+D[i]);
			use[i] = 0;
		}
	}
}
int main() {
	while(scanf("%d", &n) == 1) {
		for(i = 0; i < n; i++) {
			scanf("%d %d", &D[i], &A[i]);
			use[i] = 0;
		}
		Ans = oo;
		DFS(0, 0, 0);
		for(i = 0; i < n-1; i++)
			printf("%d ", tmp[i]+1);
		printf("%d\n", tmp[i]+1);
	}
    return 0;
}
