#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int main() {
	char s[1024];
	int cases = 0;
	while (scanf("%s", s) == 1) {
		int dpx[1024][4][2], dpy[1024][4][2];
		// [N E S W][min/max]
		const int dx[4] = {0, 1, 0, -1};
		const int dy[4] = {1, 0, -1, 0};
		int n = strlen(s);
		for (int i = 0; i <= n; i++)
			for (int j = 0; j < 4; j++) {
				dpx[i][j][0] = INF, dpx[i][j][1] = -INF;
				dpy[i][j][0] = INF, dpy[i][j][1] = -INF;
			}
		dpx[0][1][0] = 0, dpx[0][1][1] = 0;
		dpy[0][1][0] = 0, dpy[0][1][1] = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == 'F' || s[i] == '?') {
				for (int j = 0; j < 4; j++) {
					dpx[i+1][j][0] = min(dpx[i+1][j][0], dpx[i][j][0] + dx[j]);
					dpx[i+1][j][1] = max(dpx[i+1][j][1], dpx[i][j][1] + dx[j]);
					dpy[i+1][j][0] = min(dpy[i+1][j][0], dpy[i][j][0] + dy[j]);
					dpy[i+1][j][1] = max(dpy[i+1][j][1], dpy[i][j][1] + dy[j]);
				}
			} 
			if (s[i] == 'R' || s[i] == '?') {
				for (int j = 0; j < 4; j++) {
					dpx[i+1][(j+1)%4][0] = min(dpx[i+1][(j+1)%4][0], dpx[i][j][0]);
					dpx[i+1][(j+1)%4][1] = max(dpx[i+1][(j+1)%4][1], dpx[i][j][1]);
					dpy[i+1][(j+1)%4][0] = min(dpy[i+1][(j+1)%4][0], dpy[i][j][0]);
					dpy[i+1][(j+1)%4][1] = max(dpy[i+1][(j+1)%4][1], dpy[i][j][1]);
				}
			}
			if (s[i] == 'L' || s[i] == '?') {
				for (int j = 0; j < 4; j++) {
					dpx[i+1][(j+3)%4][0] = min(dpx[i+1][(j+3)%4][0], dpx[i][j][0]);
					dpx[i+1][(j+3)%4][1] = max(dpx[i+1][(j+3)%4][1], dpx[i][j][1]);
					dpy[i+1][(j+3)%4][0] = min(dpy[i+1][(j+3)%4][0], dpy[i][j][0]);
					dpy[i+1][(j+3)%4][1] = max(dpy[i+1][(j+3)%4][1], dpy[i][j][1]);
				}
			}
//			for (int j = 0; j < 4; j++) {
//				printf("%d %d %d %d\n", dpx[i][j][0], dpx[i][j][1], dpy[i][j][0], dpy[i][j][1]);
//			}
//			puts("--");
		}
		int mnx = INF, mxx = -INF, mny = INF, mxy = -INF;
		for (int i = 0; i < 4; i++) {
			mnx = min(mnx, dpx[n][i][0]);
			mxx = max(mxx, dpx[n][i][1]);
			mny = min(mny, dpy[n][i][0]);
			mxy = max(mxy, dpy[n][i][1]);
		}
		printf("Case %d: %d %d %d %d\n", ++cases, mnx, mxx, mny, mxy);
	}
	return 0;
}
