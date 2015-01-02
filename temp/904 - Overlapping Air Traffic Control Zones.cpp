#include <stdio.h>
#include <map>
using namespace std;
#define MAXN 32

void mapRelabel(map<int, int> &R, int val[]) {
	int size = 0;
	for (map<int, int>::iterator it = R.begin();
		it != R.end(); it++) {
		val[size] = it->first;
		it->second = size++;
	}
}
int main() {
	int n;
	int lx[MAXN], ly[MAXN], lz[MAXN];
	int rx[MAXN], ry[MAXN], rz[MAXN];
	int xval[MAXN], yval[MAXN], zval[MAXN];
	while (scanf("%d", &n) == 1) {
		map<int, int> RX, RY, RZ;
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d", &lx[i], &ly[i], &lz[i]);
			scanf("%d %d %d", &rx[i], &ry[i], &rz[i]);
			RX[lx[i]] = RX[rx[i]] = 1;
			RY[ly[i]] = RY[ry[i]] = 1;
			RZ[lz[i]] = RZ[rz[i]] = 1;
		} 
		mapRelabel(RX, xval);
		mapRelabel(RY, yval);
		mapRelabel(RZ, zval);
		
		int a = RX.size(), b = RY.size(), c = RZ.size();
		int sx, ex, sy, ey, sz, ez;
		int cnt[MAXN][MAXN][MAXN] = {};
		for (int i = 0; i < n; i++) {
			sx = RX[lx[i]], ex = RX[rx[i]];
			sy = RY[ly[i]], ey = RY[ry[i]];
			sz = RZ[lz[i]], ez = RZ[rz[i]];
			for (int p = sx; p < ex; p++) {
				for (int q = sy; q < ey; q++) {
					for (int r = sz; r < ez; r++) {
						cnt[p][q][r]++;
					}
				}
			}
		}
		
		int ret = 0;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				for (int k = 0; k < c; k++) {
					if (cnt[i][j][k] >= 2) {
						ret += (xval[i+1] - xval[i]) * (yval[j+1] - yval[j]) * (zval[k+1] - zval[k]);
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
