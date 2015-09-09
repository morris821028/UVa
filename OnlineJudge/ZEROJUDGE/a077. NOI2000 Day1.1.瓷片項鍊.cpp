#include <bits/stdc++.h>
using namespace std;
// D = 0.3 sqrt(V - V0) 
// assume x piece, V = Vt / x
// Length = x D = x 0.3 sqrt(Vt / x - V0)
//		  = 0.3 sqrt(Vt x - V0 x^2)
//                   ^^^^^^^^^^^^^ find maximum value
// d Vt x - V0 x^2 / dx = 0
// x = Vt / (2 V0) 
int main() {
	int Vt, V0;
	while (scanf("%d %d", &Vt, &V0) == 2) {
		double tx = (double) Vt / V0 / 2;
		if (tx - floor(tx) == 0.5)	// not unique
			puts("0");
		else
			printf("%d\n", (int) floor(tx));
	}
	return 0;
}

