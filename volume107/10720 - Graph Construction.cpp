#include <stdio.h>
#include <stdlib.h>
int cmp(const void *i, const void *j) {
	return *(int *)j - *(int *)i;
} 
int solve(int n, int deg[]) {
	int i, j;
	qsort(deg, n, sizeof(int), cmp);
	for(i = 0; i < n; i++) {
		if(deg[i] > 0) {
			for(j = i+1; j < n; j++) {
				deg[j] --;
				deg[i] --;
				if(deg[j] < 0)		return 0;
				if(deg[i] == 0)		break;
			}
		}
		if(deg[i] != 0)		return 0;
		qsort(deg+i+1, n-i-1, sizeof(int), cmp);
	}
	return 1;
}
int main() {
	int n, deg[10000], i;
	while(scanf("%d", &n) == 1 && n) {
		for(i = 0; i < n; i++)
			scanf("%d", &deg[i]);
		if(solve(n, deg))
			puts("Possible");
		else
			puts("Not possible");
	}
    return 0;
}
