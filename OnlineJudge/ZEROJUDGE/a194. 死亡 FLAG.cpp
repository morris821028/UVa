#include<stdio.h>
#include<string.h>
int map[502][502], Mt[502];
char used[502];
int mx[502], my[502];
int DFS(int now) {
	int a, i;
	for(a = Mt[now]-1; a >= 0; a--) {
		i = map[now][a];
		if(!used[i]) {
			used[i] = 1;
			if(my[i] == 0 || DFS(my[i])) {
				mx[now] = i, my[i] = now;
				return 1;
			}
		}
	}
	return 0;
}
main() {
	int n, a, b, A[501];
	while(scanf("%d", &n) == 1) {
		memset(Mt, 0, sizeof(Mt));
		for(a = 1; a <= n; a++)
			scanf("%d", &A[a]);
		for(a = 1; a <= n; a++)
			for(b = a+1; b <= n; b++)
				if(A[b] > A[a])
					map[a][Mt[a]++] = b;
		memset(mx, 0, sizeof(mx));
		memset(my, 0, sizeof(my));
		int Ans = 0;
		for(a = 1; a <= n; a++)
			if(!mx[a]) {
				memset(used, 0, sizeof(used));
				if(DFS(a))
					Ans++;
			}
		printf("%d\n", n-Ans);
	}
	return 0;
}
