#include <stdio.h>
#include <algorithm>
using namespace std;
int ymax[65536], ymin[65536], yIn[65536];
int main() {
	int testcase, n, M;
	int sx, sy, ex, ey, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &M, &n);
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);

		if (sx > ex)	swap(sx, ex);
		for (int i = 0; i < M; i++)
			ymax[i] = -0x3f3f3f3f, ymin[i] = 0x3f3f3f3f;
		for (int i = 2; i < n; i++) {
			scanf("%d %d", &x, &y);
			if (y >= sy)	ymin[x] = min(ymin[x], y);
			if (y <= sy)	ymax[x] = max(ymax[x], y);
		}
		for (int i = sx + 1; i < ex; i++)
			yIn[i] = min(ymin[i] - sy, sy - ymax[i]);
			
		yIn[sx] = yIn[ex] = 0;		
		for (int i = sx + 1; i < ex; i++)
			yIn[i] = min(yIn[i], yIn[i-1] + 1);
		for (int i = ex - 1; i > sx; i--)
			yIn[i] = min(yIn[i], yIn[i+1] + 1);
		long long ret = 0;
		for (int i = sx + 1; i < ex; i++) {
			if (yIn[i]) {
				ret++;
				ret += min(yIn[i] - 1, M - sy - 1);
				ret += min(yIn[i] - 1, sy);
			}
		}
		printf("%lld\n", ret);
	}
	return 0;
}
