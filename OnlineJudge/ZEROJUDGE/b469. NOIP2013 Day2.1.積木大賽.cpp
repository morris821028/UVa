#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, x;
	while (scanf("%d", &n) == 1) {
		int pre = 0, ret = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			if (x > pre)	
				ret += x - pre;
			pre = x;			
		}
		printf("%d\n", ret);
	}
	return 0;
}

