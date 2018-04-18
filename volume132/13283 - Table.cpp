#include <bits/stdc++.h> 
using namespace std;
const int MAXXY = 2005;
int8_t g[MAXXY][MAXXY];
int cnt[MAXXY][MAXXY];
int main() {
	int X, Y, N, D;
	while (scanf("%d %d %d %d", &X, &Y, &N, &D) == 4) {
		for (int i = 0; i < X; i++)
			memset(g[i], 0, sizeof(g[0][0])*Y);
		for (int i = 0; i <= X; i++)
			memset(cnt[i]+1, 0, sizeof(cnt[0][0])*Y);
		for (int i = 0; i < N; i++) {
			int lx, ly, rx, ry;
			scanf("%d %d %d %d", &lx, &rx, &ly, &ry);
			for (int x = lx; x < rx; x++) {
				for (int y = ly; y < ry; y++)
					g[x][y] = 1;
			}
		}

		static int16_t h[MAXXY];
		memset(h, 0, sizeof(h[0])*Y);
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++)
				h[j] = g[i][j] ? 0 : h[j]+1;
			// histogram
			h[Y] = 0;
			static pair<int, int> stk[MAXXY];
			int stkIdx = -1;
			stk[++stkIdx] = {0, -1};	// <height, position>
			for (int j = 0; j <= Y; j++) {
				int hh = h[j], yy = j;
				while (hh < stk[stkIdx].first) {
					yy = stk[stkIdx].second;
					int width = j-yy;
					cnt[stk[stkIdx].first][width]++;
					stkIdx--;
					cnt[max(stk[stkIdx].first, hh)][width]--;
				}
				stk[++stkIdx] = {hh, yy};
			}
		}

		for (int i = 1; i <= X; i++) {
			for (int j = Y, s = 0; j >= 1; j--)
				s += cnt[i][j], cnt[i][j] = s;
			for (int j = Y, s = 0; j >= 1; j--)
				s += cnt[i][j], cnt[i][j] = s;
		}

		for (int i = X-1; i >= 1; i--) {
			for (int j = 1; j <= Y; j++)
				cnt[i][j] += cnt[i+1][j];
		}

		for (int i = 0; i < D; i++) {
			int h, w;
			scanf("%d %d", &h, &w);
			printf("%d\n", cnt[h][w]);
		}
//		for (int i = 1; i <= X; i++) {
//			for (int j = 1; j <= Y; j++)
//				printf("%d ", cnt[i][j]);
//			puts("");
//		}
	}
	return 0;
}
/*
7  5  3  9
1  2  0  1
5  7  2  5
0  1  2  4
7  1
3  5
5  3
2  2
3  3
4  4
4  5
6  2
1  1
*/
