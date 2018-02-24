#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100005;
static int n, m, t[MAXN];
int main() {
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &t[i]);
		sort(t, t+n);
		int g = 0;
		for (int i = 1; i < n; i++)
			g = __gcd(g, t[i]-t[i-1]);
		g = g*2;
		for (int i = 0; i < m; i++) {
			int st, ed;
			scanf("%d %d", &st, &ed);
			int ret = 0;
			if (n == 1) {
				if (2*t[0]-st == ed)
					ret = 1;
			} else {
				if ((ed-st)%g == 0) {
					ret = 1;
				} else {
					for (int i = 0; i < n; i++) {
						if ((2*t[i]-st-ed)%g == 0) {
							ret = 1;
							break;
						}
					}
				}
			}
			putchar(ret ? 'Y' : 'N');
			putchar(i == m-1 ? '\n' : ' ');
		}
	}
	return 0;
}
