#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	static int a[500000];
	while (scanf("%d %d", &n, &k) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		int c = 0;
		for (int i = 0; i < n; i++) {
			int mn = a[i], mx = a[i];
			int sum = a[i];
			for (int j = i+1; j < n; j++) {
				sum += a[j];
				mn = min(mn, a[j]);
				mx = max(mx, a[j]);
				if ((sum-mn-mx)%k == 0)
					c++;
			}
		}
		printf("%d\n", c);
	}
	return 0;
}
