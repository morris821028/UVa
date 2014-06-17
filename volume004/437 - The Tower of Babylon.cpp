#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x, y, z;
}Block;
void swap(int *a, int *b) {
	int tmp;
	tmp = *a, *a = *b, *b = tmp;
}
int cmp(const void *i, const void *j) {
	Block *a, *b;
	a = (Block *)i, b = (Block *)j;
	return b->x - a->x;
}
int main() {
	int n, i, j, Case = 0;
	Block D[91];
	while(scanf("%d", &n) == 1 && n) {
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &D[i].x, &D[i].y, &D[i].z);
			if(D[i].y > D[i].x)
				swap(&D[i].x, &D[i].y);
			D[n+i] = D[i];			
			swap(&D[n+i].x, &D[n+i].z);
			if(D[n+i].y > D[n+i].x)
				swap(&D[n+i].x, &D[n+i].y);
				
			D[2*n+i] = D[i];
			swap(&D[2*n+i].y, &D[2*n+i].z);
			if(D[2*n+i].y > D[2*n+i].x)
				swap(&D[2*n+i].x, &D[2*n+i].y);
		}
		qsort(D, 3*n, sizeof(Block), cmp);
		int DP[90] = {};
		for(i = 0; i < 3*n; i++)
			DP[i] = D[i].z;
		for(i = 0; i < 3*n; i++) {
			for(j = i+1; j < 3*n; j++) {
				if((D[i].x > D[j].x && D[i].y > D[j].y) ||
					(D[i].x > D[j].y && D[i].y > D[j].x)) {
					if(DP[j] < DP[i]+D[j].z) {
						DP[j] = DP[i] + D[j].z;
					}
				}
			}
		}
		int ans = 0;
		for(i = 0; i < 3*n; i++)
			ans = ans > DP[i] ? ans : DP[i];
		printf("Case %d: maximum height = %d\n", ++Case, ans);
	}
    return 0;
}
