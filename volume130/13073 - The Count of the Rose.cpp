#include <bits/stdc++.h>
using namespace std;

int f(int n) {
	int ret = 0, t = 10;
	for (int i = 1; ; i++) {
		if (n >= t) {
			ret += 9 * (t/10) * i;
		} else {
			ret += (n - t/10 + 1) * i;
			return ret;
		}
		t = t * 10;
	}
	return 0;
}
int main() {
	int a, b;
	while (scanf("%d %d", &a, &b) == 2 && a) {
		int l = a, r = b, mid, ret = -1, retv = -1;
		int tot = f(b) - f(a-1);
		while (l <= r) {
			mid = (l + r)/2;
			int t = f(mid) - f(a-1);
			if (t <= tot / 2)
				l = mid+1, ret = mid, retv = t;
			else
				r = mid-1;
		}
		printf("%d\n", ret);
	}
	return 0;
}

