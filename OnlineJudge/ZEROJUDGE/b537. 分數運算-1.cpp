#include <bits/stdc++.h>
using namespace std;
pair<int, int> reduce(int a, int b) {
	int g = __gcd(a, b);
	return {a/g, b/g};
}
int main() {
	int a, b;
	while (scanf("%d %d", &a, &b) == 2) {
		int v[100] = {}, it = 0;
		while (a != b) {
			if (a > b)
				v[it++] = 0, a = a-b;
			else
				v[it++] = 1, swap(a, b);
			pair<int, int> r = reduce(a, b);
			a = r.first, b = r.second;
		}
		long long ret = 1;
		for (int i = it-1; i >= 0; i--)
			if (v[i])	ret++;
			else		ret <<= 1;
		printf("%lld\n", ret);
	}
	return 0;
}

