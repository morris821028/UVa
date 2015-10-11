#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		unsigned long long a[3];
		scanf("%llu %llu %llu", &a[0], &a[1], &a[2]);
		sort(a, a+3);
		if (a[0]*a[0] == a[2]*a[2] - a[1]*a[1])
			puts("right triangle");
		else if (a[0]*a[0] > a[2]*a[2] - a[1]*a[1])
			puts("acute triangle");
		else
			puts("obtuse triangle");
	}
	return 0;
}

