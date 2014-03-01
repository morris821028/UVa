#include <stdio.h>
#include <stdlib.h>
int main() {
	int n, m, p;
	while(scanf("%d %d %d", &n, &m, &p) == 3) {
		if(n == 0 && m == 0 && p == 0)	break;
		int i, j, k;
		int map[101][101];
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				scanf("%d", &map[i][j]);
				if(map[i][j] == 0)	map[i][j] = 5;
				else if(map[i][j] == 1)	map[i][j] = 10;
				else	map[i][j] = -1;
			}
		} 
		/*
		for(i = 0; i < n; i++, puts("")) {
			for(j = 0; j < m; j++)
				printf("%2d ", map[i][j]);
		}*/
		int max = 0, width, length, tmp = 0;
		for(i = 0; i < n; i++) {
			int sum[100] = {}, cant[100] = {};
			for(j = i; j < n; j++) {
				width = j-i+1, length = 0, tmp = 0;
				for(k = 0; k < m; k++) {
					if(map[j][k] == -1 || cant[k] == 1) {
						if(map[j][k] == -1)	cant[k] = 1;
						length = 0;
						tmp = 0;
					}
					else {
						length++;
						sum[k] += map[j][k];
						tmp += sum[k];
					}
					if(length == width) {
						/*printf("%d %d %d %d\n", tmp, j, k, length);*/
						if(p >= tmp) {
							if(max < width * width) {
								max = width*width;
							}
						}
						tmp -= sum[k-length+1];
						length--;
					}
				}
			}
		}
		printf("%d\n", max);
	}
    return 0;
}/*
4 5 50
1 0 2 2 0
0 1 1 0 0
0 2 1 1 1
1 0 0 1 0
5 5 3
2 0 1 0 1
2 0 2 2 0
1 0 0 1 0
0 2 0 2 2
0 2 2 0 0
*/
