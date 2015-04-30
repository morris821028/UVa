#include <stdio.h> 
#include <algorithm>
#include <math.h>
using namespace std;

const int MAXN = 32;
const int INF = 0x3f3f3f3f;
int C[MAXN], P[MAXN], L[MAXN];
// a x + by = g
void exgcd(int x, int y, int &g, int &a, int &b) {
	if (y == 0)
		g = x, a = 1, b = 0;
	else
		exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
int hasCollision(int m, int n) {
	// assume m caves arranged in a circle
	// ci + k * pi = a * m  --- (1)
	// cj + k * pj = b * m  --- (2)
	// (2)-(1) 	=> (ci - cj) + k * (pi - pj) = m * (a - b)
	//			=> (a - b) * m + k * (pj - pi) = ci - cj
	// check k in [0, min(L[i], L[j])] has a solution.
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			int x = P[j] - P[i], y = m, z = C[i] - C[j];
			int a, b, g;
			int limitR = min(L[i], L[j]), limitL = 0;
			exgcd(x, y, g, a, b);
		
			if (z%g)	continue;
			a = a * (z / g);
			// ax + by = z
			// a = a + lcm(x, y)/x * k, b = b + lcm(x, y)/y * k
			// a = a + y / g * k, b = b + x / g * k
			// minmum a, a >= 0
			if (g < 0)	g = -g;
			a = (a%(y/g) + y/g) % (y/g);
			if (a <= limitR)
				return true;
		}
	}
	return false;
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		int m = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d", &C[i], &P[i], &L[i]);
			m = max(m, C[i]);
		}
			
		int ret = -1;
		for (int i = m; i < 99999999; i++) {
			
			if (!hasCollision(i, n)) {
				ret = i;
				break;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2

3
1 3 4
2 7 3
3 2 1

5
1 2 14
4 4 6
8 5 9
11 8 13
16 9 10
*/
