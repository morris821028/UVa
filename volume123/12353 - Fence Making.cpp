#include <bits/stdc++.h>
using namespace std;

int main() {
	int64_t rmn, rmx, dmn, dmx, s;
	const double pi = acos(-1);
	while (scanf("%lld %lld %lld %lld %lld", &rmn, &rmx, &dmn, &dmx, &s) == 5) {
		if (rmn + rmx + dmn + dmx + s == 0)
			break;
		int64_t ret = 0;
		for (int r = rmn; r <= rmx; r++) {
			for (int d = dmn; d <= dmx; d++) {
				double area = 4.0*s*(d+r) - 2.0*pi*r*r;
				double t = 8.0*(r+d)*(r+d) - 2.0*pi*r*r;
				ret += floor(area/t)*2LL;
			}
		}
		printf("%lld\n", ret);
	}
	return 0;
}
