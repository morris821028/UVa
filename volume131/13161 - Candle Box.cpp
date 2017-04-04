#include <bits/stdc++.h>
using namespace std;

int main() {
	int D, R, T;
	while (scanf("%d %d %d", &D, &R, &T) == 3) {
		int x = 0, y = 0;
		int a = 0, b = 0;
		while (true) {
			x++;
			if (x >= 4)	
				a += x;
			if (x-y > D) {
				y++;
				if (y >= 3)
					b += y;
			}
			if (a + b == R + T)
				break;
		}
		printf("%d\n", R-a);
	}
	return 0;
}

