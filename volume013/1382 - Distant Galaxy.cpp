#include <stdio.h> 
#include <map>
#include <algorithm>
using namespace std;

int main() {
	int n, x[128], y[128];
	int cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		map<int, int> Rx, Ry;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x[i], &y[i]);
			Rx[x[i]] = 0, Ry[y[i]] = 0;
		}
		
		int size, R, C;
		size = 0;
		for (map<int, int>::iterator it = Rx.begin();
			it != Rx.end(); it++) {
			it->second = size++;
		}
		R = size;
		size = 0;
		for (map<int, int>::iterator it = Ry.begin();
			it != Ry.end(); it++) {
			it->second = size++;
		}
		C = size;
		
		int g[128][128] = {}, ret = 0;
		for (int i = 0; i < n; i++) {
			int r, c;
			r = Rx[x[i]], c = Ry[y[i]];
			g[r][c]++;
		}
		
		for (int i = 0; i < R; i++) {
			int sum[128] = {}, s1, s2, mn;
			for (int j = i; j < R; j++) {
				s1 = s2 = 0, mn = 0;
				for (int k = 0; k < C; k++) {
//					printf("[%d %d] %d\n", i, j, k);
					sum[k] += g[j][k];
					s1 += g[i][k], s2 += g[j][k];
					if (i != j) {
//						printf("%d %d %d %d = %d\n", s1, s2, mn, sum[k], s1 + s2 - mn + sum[k]);
						ret = max(ret, s1 + s2 - mn + sum[k] - g[i][k] - g[j][k]);
						mn = min(mn, s1 + s2 - sum[k]);
					}
				}
			}
		}
		
		for (int i = 0; i < R; i++) {
			int sum = 0;
			for (int j = 0; j < C; j++)
				sum += g[i][j];
			ret = max(ret, sum);
		}
		
		for (int i = 0; i < C; i++) {
			int sum = 0;
			for (int j = 0; j < R; j++)
				sum += g[j][i];
			ret = max(ret, sum);
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
10 
2 3 
9 2 
7 4 
3 4 
5 7 
1 5 
10 4 
10 6 
11 4 
4 6 

3
1 1
2 1
3 1

3
1 1
1 2
1 3

9
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
*/
