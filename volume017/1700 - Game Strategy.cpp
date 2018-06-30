#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	while (scanf("%d", &n) == 1) {
		char cmd[26];
		static int ew[1<<20], e;
		static int* g[26];
		static int gn[26];
		e = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &m);
			g[i] = ew + e, gn[i] = m;
			for (int j = 0; j < m; j++) {
				scanf("%s", cmd);
				int mask = 0, k;
				for (k = 0; cmd[k]; k++)
					mask |= 1<<(cmd[k]-'a');
				ew[e++] = mask;
			}
		}
		
		int ret[26][26];
		memset(ret, -1, sizeof(ret));
		for (int goal = 0; goal < n; goal++) {
			int visited = 1<<goal;
			ret[goal][goal] = 0;
			for (int dist = 1; ; dist++) {
				int next = visited;
				for (int i = 0; i < n; i++) {
					if ((visited>>i)&1)
						continue;

#define UNLOOP(i, j) {	int e = g[i][j]; \
						if ((visited&e) == e) { \
							next |= 1<<i; \
							ret[i][goal] = dist; \
							break; \
						} }
#define UNLOOP4(i, j) {}
					int m = gn[i], j;
					for (j = 0; j + 8 <= m; j += 8) {
						UNLOOP(i, j);
						UNLOOP(i, j+1);
						UNLOOP(i, j+2);
						UNLOOP(i, j+3);
						UNLOOP(i, j+4);
						UNLOOP(i, j+5);
						UNLOOP(i, j+6);
						UNLOOP(i, j+7);
					}
					for (; j < m; j++)
						UNLOOP(i, j);
//					for (int j = 0; j < gn[i]; j++) {
//						int e = g[i][j];
//						if ((visited&e) == e) {
//							next |= 1<<i;
//							ret[i][goal] = dist;
//							break;
//						}
//					}
				}
				if (next == visited)
					break;
				visited = next;
			}
		}
		
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				printf("%d%c", ret[i][j], " \n"[j==n-1]);
		}
	}
	return 0;
}
/*
2
2 ab b
1 b
3
1 b
2 b a
2 ab ac
*/
