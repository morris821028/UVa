#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main() {
	int n, m, p;
	scanf("%d", &n);
	while(n--) {
		scanf("%d %d", &m, &p); 
		int map[11][11] = {0}, i, x, y, j, k;
		for(i = 0; i < p; i++) {
			scanf("%d %d", &x, &y);
			map[x][y] = 1;
			map[y][x] = 1;
		}
		int Used[30] = {0}, max = 0;
		for(i = 1; i <= m; i++) {
			if(Used[i] == 0) {
				Used[i] = 1;
				int Q[1000], Qt, tn;
				Qt = 0, Q[Qt] = i;
				for(j = 0; j <= Qt; j++) {
					tn = Q[j];
					for(k = 1; k <= m; k++) {
						if(map[tn][k] == 1 && Used[k] == 0) {
								Used[k] = 1;
								Q[++Qt] = k;
						}
					}
				} 
				if(max < Qt+1)	max = Qt+1;
			}
		}
		printf("%d\n", max);
		if(n)	puts("");
	}
    return 0;
}
