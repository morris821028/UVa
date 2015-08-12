#include <bits/stdc++.h> 
using namespace std;

int main() {
	int testcase, x, y, z;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &x, &y, &z);
		if (y <= z) {
			puts(y < x ? "Poor Snail" : "1");
			continue;
		}
		int days = (x - y) / (y - z);
		int sum = (y - z) * days;
		while (sum < x) {
			days++;
			if (sum + y >= x)
				break;
			sum += y - z;
		}
		printf("%d\n", days);
	}
	return 0;
}
