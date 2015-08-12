#include <bits/stdc++.h>
using namespace std;

int main() {
	int x, y;
	while (scanf("%d %d", &x, &y) == 2)
		x--, y--, printf("%llu\n", (1LLU)<<(x*8+y));
	return 0;
}
