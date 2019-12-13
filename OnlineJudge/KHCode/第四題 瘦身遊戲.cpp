#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	static int pos[1000005];
	while (scanf("%d", &n) == 1) {
		int x;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			pos[x] = i;
		}

		int ret = 0;
		for (int i = 1; i <= n; ) {
			while (i <= n && pos[i] > pos[i-1])
				i++;
			if (i <= n)
				ret++;
			while (i <= n && pos[i] < pos[i-1])
				i++;
			if (i <= n)
				ret++;
		}
		printf("%d\n", ret);
	}
	return 0;
}
