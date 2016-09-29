#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int ret = 1, x, p;
		for (int i = 0; i < 5; i++) {
			scanf("%d", &x);
			if (i)
				ret &= x == p+1;
			p = x;
		}
		puts(ret ? "Y" : "N");
	}
	return 0;
}

