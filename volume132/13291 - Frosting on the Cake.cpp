#include <bits/stdc++.h> 
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int64_t a[3] = {}, b[3] = {}, x;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			a[i%3] += x;
		}
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			b[i%3] += x;
		}
		
		int64_t ret[3] = {};
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				ret[(i+j)%3] += a[i]*b[j];
		printf("%lld %lld %lld\n", ret[1], ret[2], ret[0]);
	}
	return 0;
}
