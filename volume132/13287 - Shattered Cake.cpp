#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, w;
	while (scanf("%d %d", &w, &n) == 2) {
		int a, b;
		int64_t s = 0;
		for (int i = 0; i < n; i++)
			scanf("%d %d", &a, &b), s += a*b;
		printf("%lld\n", s/w);
	}
	return 0;
}
