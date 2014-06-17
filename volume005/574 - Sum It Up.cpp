#include <stdio.h>
int target, n, A[20], i;
int flag, choose[20], last[20];
void DFS(int now, int sum, int t) {
	if(sum == target) {
		int i;
		for(i = 0; i < n; i++)
			if(choose[i] != last[i])
				break;
		if(i == n)	return;
		for(i = 0; i < t; i++) {
			if(i)	printf("+");
			printf("%d", choose[i]);
			last[i] = choose[i];
		}
		puts("");
		for(; i < n; i++)	last[i] = -1;
		flag = 1;
		if(A[now])
			return;
	}
	if(now == n || sum > target)	return;
	choose[t] = A[now];
	DFS(now+1, sum+A[now], t+1);
	choose[t] = -1;
	DFS(now+1, sum, t);
}
int main() {
	while(scanf("%d %d", &target, &n) == 2) {
		if(n == 0)	break;
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]), last[i] = -1, choose[i] = -1;
		printf("Sums of %d:\n", target);
		flag = 0;
		DFS(0, 0, 0);
		if(flag == 0)	puts("NONE");
	}
    return 0;
}
