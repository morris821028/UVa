#include <bits/stdc++.h>
using namespace std;

int main() {
	int64_t n;
	while (scanf("%lld", &n) == 1) {
		if (n < 3)
			printf("0\n");
		else
			printf("%lld\n", (n-2)*(n-1)/2);
	}
	return 0;
}
