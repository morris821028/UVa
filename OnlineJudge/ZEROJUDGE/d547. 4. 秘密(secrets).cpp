#include<stdio.h>
#include<stdlib.h>
main() {
	int n, m;
	while(scanf("%d %d", &n, &m) == 2) {
		int ans[100], a, b;
		int data[100][100];
		for(a = 0; a < m; a++)
			scanf("%d", &ans[a]);
		for(a = 0; a < n; a++) {
			for(b = 0; b <= m; b++)
				scanf("%d", &data[a][b]);
		}
		for(a = 0; a < n; a++) {
			int t = {data[a][m]}, flag = 0;
			for(b = m-1; b >= 0; b--) {
				if(t >= data[a][b]) {
					if(ans[b] != 1) {flag = 1;}
				}
				else {
					if(ans[b] != 0) {flag = 1;}
				}
				t = abs(data[a][b+1] - data[a][b]);
			}
			if(flag == 0) {
				for(b = 0; b <= m; b++)
					printf("%d ", data[a][b]);
				puts("");break;
			}
		}
	}
	return 0;
}
