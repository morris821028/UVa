#include <bits/stdc++.h>
using namespace std;

int unfold(int L, int W, int H, int x1, int y1,
		int x2, int y2, int z2, int rx, int ry) {
	if (z2 == 0)
		return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	int ret = 0x3f3f3f3f;
	if (rx >= 0 && rx < 2)
		ret = min(ret, unfold(H, W, L, x1+H, y1, H-z2, y2, x2, rx+1, ry));
	if (rx <= 0 && rx > -2)
		ret = min(ret, unfold(H, W, L, x1-L, y1, z2, y2, L-x2, rx-1, ry));
	if (ry >= 0 && ry < 2)
		ret = min(ret, unfold(L, H, W, x1, y1-W, x2, z2, W-y2, rx, ry+1));
	if (ry <= 0 && ry > -2)
		ret = min(ret, unfold(L, H, W, x1, y1+H, x2, H-z2, y2, rx, ry-1));
	return ret;
}

int dist2(int L, int W, int H, int x1, int y1, int z1, 
		int x2, int y2, int z2) {
	// move (x1, y1, z1) to x-y plane
	if (z1 != 0 && z1 != H) {
		if (y1 != 0 && y1 != W) {
			swap(L, H), swap(x1, z1), swap(x2, z2);
		} else {
			swap(W, H), swap(y1, z1), swap(y2, z2);
		}
	}
	if (z1 == H)
		z1 = 0, z2 = H - z2;
	int ret = unfold(L, W, H, x1, y1, x2, y2, z2, 0, 0);
	return ret;
}

int main() {
	int L, W, H, x1, y1, z1, x2, y2, z2;
	while (scanf("%d %d %d %d %d %d %d %d %d", &L, &W, &H, &x1, &y1, &z1, &x2, &y2, &z2) == 9) {
		int ret = dist2(L, W, H, x1, y1, z1, x2, y2, z2);
		printf("%d\n", ret);
	}
	return 0;
}
/*
5 5 2 3 1 2 3 5 0
300 600 900 300 550 0 0 550 900
*/
