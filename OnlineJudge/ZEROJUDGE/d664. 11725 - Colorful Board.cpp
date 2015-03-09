#include<stdio.h>
#include<string.h>
void change(int n, char *s) {
	if(n == 0) return;
	change(n/5, s+1);
	*s = n%5;
}
int Calu(int n, char *s) {
	if(n == 0) return 0;
	return Calu(n-1, s+1)*5+(*s);
}
main() {
	int T, n, m, K, x, y, C = 1;
	int map[8][8], s5[10] = {1};
	int i, j, k, l;
	for(i = 1; i < 10; i++)
		s5[i] = s5[i-1]*5;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &m, &n);
		scanf("%d", &K);

		memset(map, 0, sizeof(map));
		for(i = 0; i < K; i++) {
			scanf("%d %d", &x, &y);
			map[x][y] = 1;
		}
		m++, n++;
		int last[78126], now[78126];
		int state = s5[n]-1, tmp, now_state;
		char CH[10];
		memset(last, 0, sizeof(last));
		last[0] = 1;
		for(i = 0; i < m; i++) { 
			for(j = 1; j <= n; j++) {
				for(k = 0; k <= state; k++) {
					memset(CH, 0, sizeof(CH));
					change(k, CH);
					if(last[k] == 0)	continue;
					if(j != 1 && CH[j-2] == 0 && map[i+1][j-1] == 0)	continue;
					if(j != 1 && CH[j-2] != 0 && map[i+1][j-1] != 0)	continue;
					if(map[i+1][j]) {
						CH[j-1] = 0;
						now_state = Calu(n, CH);
						now[now_state] = (now[now_state] + last[k])%1000000007;
					} else {
						for(l = 1; l <= 4; l++) {
							if(CH[j-1] != l && (j == 1 || CH[j-2] != l)) {
								tmp = CH[j-1], CH[j-1] = l;
								now_state = Calu(n, CH);
								now[now_state] = (now[now_state] + last[k])%1000000007;
								CH[j-1] = tmp;
							}
						}
					}
				}
				for(k = 0; k <= state; k++)
					last[k] = now[k], now[k] = 0;
			}
		}
		int Ans = 0;
		for(i = 0; i <= state; i++)
			Ans = (Ans+last[i])%1000000007;
		printf("Case %d: %d\n", C++, Ans);
	}
	puts("OLE");
	return 0;
}
