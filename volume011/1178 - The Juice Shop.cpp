#include <bits/stdc++.h>
using namespace std;

// a x + by = g
void exgcd(int x, int y, int &g, int &a, int &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}

void printStep(int n, int x) {
	if (x == 0)
		printf("%d liter(s) not needed\n", n);
	else if (x < 0)
		printf("%d liter(s) withdrawn %d times\n", n, -x);
	else
		printf("%d liter(s) poured %d times\n", n, x);
}

int main() {
	int n, m;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		if (cases++)
			puts("");
			
		int g, a, b;		
		exgcd(n, m, g, a, b);
		printf("minimum volume: %d liter(s)\n", g);
		printStep(n, a);
		printStep(m, b);
	}
	return 0;
}

/*
3240 1376
2607 79
*/
