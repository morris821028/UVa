#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int a[512], b[512], cnt[360] = {};
		for (int i = 0; i < n; i++) {
			scanf("%*d %d %d", &a[i], &b[i]);
			a[i] = (a[i]%360 + 360)%360;
			cnt[a[i]]++;
		}
		int ret = -1;
		for (int time = 0; time <= 360 && ret == -1; time++) {
			for (int i = 0; i < 360; i++) {
				if (cnt[i] > 1)
					ret = time;
				cnt[i] = 0;
			}
			for (int i = 0; i < n; i++) {
				a[i] = a[i] + b[i];
				a[i] = (a[i]%360 + 360)%360;
				cnt[a[i]]++;
			}
		}
		if (ret == -1)
			printf("GIANIK IS NEVER ECLIPSED\n");
		else
			printf("%d\n", ret);
	}
	return 0;
}

