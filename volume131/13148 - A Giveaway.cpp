#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		long long d1 = pow(n, 0.5), d2 = pow(n, 0.3);
		while (d1*d1 < n)
			d1++;
		while (d2*d2*d2 < n)
			d2++;
		if (d1*d1 == n && d2*d2*d2 == n)
			puts("Special");
		else
			puts("Ordinary");
	}
	return 0;
}

