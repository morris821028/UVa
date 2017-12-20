#include <bits/stdc++.h> 
using namespace std;

int64_t dist(int64_t sx, int64_t sy, int64_t ex, int64_t ey) {
	if (sx == ex)
		return llabs(sy-ey);
	if (sx > ex)
		return dist(ex, ey, sx, sy);
	if (sy > ey)
		return dist(sx, sy, ex, sy+(sy-ey));
	if (ex - sx <= ey - sy)
		return (ex - sx) + (ey - sy);
	// complex cases, snake on y-axis
	// (1) on the same y-axis
	sx += ey - sy;
	int64_t ret = (ey - sy)*2;
	// (2) snake on same y-axis
	if (sx%2 != ex%2)	// different parity, walk into next row
		ret += (sx+ey)%2 ? 3 : 1, sx++;
	ret += (ex - sx)*2;
	return ret;
}
int main() {
	int64_t sx, sy, ex, ey;
	while (scanf("%lld %lld %lld %lld", &sx, &sy, &ex, &ey) == 4 && sx) {
		printf("%lld\n", dist(sx, sy, ex, ey));
	}
	return 0;
}
