#include <stdio.h>
#include <string.h>
#include <queue>
#include <functional>
#include <deque>
#include <algorithm>
using namespace std;

char sg[128][128];
int ig[128][128];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
const char dd[] = "><v^";
//				  >   <  v  ^
int main() {
	int testcase, n, m, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", sg[i]);
		
		int idx = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sg[i][j] != '.') {
					ig[i][j] = idx++;
				}
			}
		}
		
		int match = 0, ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sg[i][j] != '.') {
					int odd = 0;
					for (int k = 0; k < 4; k++)
						if (dd[k] == sg[i][j])
							odd = k;
					int cost = 1, mm = 0;
					for (int k = 0; k < 4; k++) {
						int x = i, y = j;
						x += dx[k], y += dy[k];
						while (x < n && x >= 0 && y < m && y >= 0) {
							if (sg[x][y] != '.') {
								if (k == odd)
									cost = 0;
								mm = 1;
								break;
							}
							x += dx[k], y += dy[k];
						}
					}
					match += mm, ret += cost;
				}
			}
		}
		
		printf("Case #%d: ", ++cases);
		if (match != idx)
			puts("IMPOSSIBLE");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
999
4 1
<
^
^
>
*/

