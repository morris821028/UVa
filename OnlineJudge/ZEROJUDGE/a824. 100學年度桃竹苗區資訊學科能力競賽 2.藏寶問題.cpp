#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b, c;
	while (scanf("%d %d %d", &a, &b, &c) == 3) {
		int ret = -1;
		for (int i = 1; i <= c; i++)
			if (i%a == 0 || i%b == 0)
				ret += i;
		printf("%c\n", (ret%26 + 26)%26 + 'A');
	}
	return 0;
}

