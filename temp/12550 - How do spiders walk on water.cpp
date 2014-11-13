#include <stdio.h> 
#include <algorithm>
#include <sstream> 
#include <iostream>
using namespace std;

char line[1048576];
pair<double, double> solve(double a1, double b1, double c1, double a2, double b2, double c2) {
	// a1 x + b1 y = c1, a2 x + b2 y = c2
	double dx, dy, d;
	d = a1 * b2 - b1 * a2;
	dx = c1 * b2 - b1 * c2;
	dy = a1 * c2 - a2 * c1;
	return make_pair(dx / d, dy / d);
}
int main() {
	int D, P;
	while (gets(line)) {
		stringstream sin(line);
		sin >> D >> P;
		double d[32767];
		int n = 0;
		while (sin >> d[n])	n++;
		int pos = 0;

		if (n < D + 1) {
			pair<double, double> sol = solve(d[n-4], d[n-3], d[n-2], d[n-3], d[n-2], d[n-1]);
//			printf("%lf %lf\n", sol.first, sol.second);
			for (int i = n; i < D + 1; i++, n++) {
				d[i] = sol.first * d[i-2] + sol.second * d[i-1];
				if (P < d[i])	break;
			}
		}		
		for (int i = 0; i < D + 1; i++) {
			if (P < d[i])	break;
			pos++;
		}
		if (pos == D + 1)
			puts("The spider may fall!");
		else if (pos == 0)
			puts("The spider is going to fall!");
		else
			printf("%d\n", D - pos + 1);
	}
	return 0;
}
/*
3 3 0 1 1 1
10 2 0 1 1 2
10 3 0 1 1 2
10 4 0 1 1 2
10 5 0 1 1 2
10 6 0 1 1 2
10 7 0 1 1 2
10 8 0 1 1 2
10 9 0 1 1 2
10 3 1 1 2 2 2 3 3 3 3 4 4
10 5 1 1 2 2 2 3 3 3 3 4 4
10 5 6 6 6 6 8 8 8 11 30 41 42
10 2 0 1 1 1 1 1 1 1 1 1 1
50 200 0 3 6 15 36
*/
