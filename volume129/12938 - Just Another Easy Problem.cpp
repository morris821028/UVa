#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		char n[16], m[16];
		scanf("%s", n);

		int ret = 0;
		for (int i = 32; i < 100; i++) {
			sprintf(m, "%d", i*i);
			int diff = 0;
			for (int j = 0; j < 4; j++)
				diff += n[j] != m[j];
			if (diff == 1)
				ret ++;
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}