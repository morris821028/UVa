#include <bits/stdc++.h>
using namespace std;

int isSierpinskiCarpetPixelFilled(int64_t x, int64_t y) {
	int ret = 0;
	const int64_t MOD = 1000000;
	set<int> SX, SY;
    while (x > 0 || y > 0) {
    	int64_t ix = x*3/MOD;
    	int64_t iy = y*3/MOD;
        if (ix == 1 && iy == 1)
            return ret;
        x = x*3 - ix*MOD, y = y*3 - iy*MOD;
        if (SX.count(x) || SY.count(y))
        	return -1;
        SX.insert(x), SY.insert(y);
        ret++;
    }
    return -1;
}
int main() {
	int testcase, cases = 0;
	char sx[16], sy[16];
	scanf("%d", &testcase);
	while (testcase--) {
		int64_t x, y; 
		scanf("%s %s", sx, sy);
		sscanf(sx+2, "%lld", &x);
		sscanf(sy+2, "%lld", &y);
		for (int i = strlen(sx)-2; i < 6; i++)
			x = x*10;
		for (int i = strlen(sy)-2; i < 6; i++)
			y = y*10;
		int ret = isSierpinskiCarpetPixelFilled(x, y);
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
2
0.111 0.111
0.123 0.123

3
0.99 0.99
0.3 0.3
0.99999 0.99999
*/
