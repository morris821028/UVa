#include<stdio.h>
#include<string.h>
#define oo 100000
int map[16][16], Best[65537];
int n, i, j;
int DP(int N, int sum) {
	if(N == 0)	return 0;
	if(Best[N] != -oo)
		return Best[N];
	if(Best[sum] == -oo)
		Best[sum] = DP(sum, 0);
	int i, j, tmp;
	for(i = 0; i < n; i++) {
		if(N&(1<<i)) {
			for(j = i+1; j < n; j++) {
				if(N&(1<<j)) {
					tmp = DP(N-(1<<i)-(1<<j), sum+(1<<i)+(1<<j));
					Best[N] = Best[N] > tmp+map[i][j] ? Best[N] : tmp+map[i][j];
				}
			}
			break;
		}
	}
	return Best[N];
}
int main() {
	while(scanf("%d", &n) == 1) {
		n *= 2;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%d", &map[i][j]);
		for(i = (1<<n)-1; i >= 0; i--)
			Best[i] = -oo;
		printf("%d\n", DP((1<<n)-1, 0)*10);
	}
	return 0;
}
