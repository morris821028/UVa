#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		static int used[131072] = {}, cases = 0;
		int n, x = 1;
		scanf("%d", &n);
		cases++;
		putchar('0'), putchar('.');
		used[x] = cases;
		while (x) {
			int y = (x*10)/n;
			putchar('0'+y);
			x = (x*10)%n;
			if (used[x] == cases)
				break;
			used[x] = cases;
		}
		puts("");
	}
	return 0;
}

