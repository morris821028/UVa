#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <set>
#include <algorithm>
using namespace std;
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
#define eps 1e-3
struct cmp {
	bool operator()(const pair<double, double> pa, const pair<double, double> pb) const {
		if (fabs(pa.first - pb.first) > eps)
			return pa.first < pb.first;
		if (fabs(pa.second - pb.second) > eps)
			return pa.second < pb.second;
		return false;
	}
};
double Rosenbrock(double x, double y) {
	return pow(1-x, 2) + 100 * pow(y - x*x, 2);
}
main() {
	int n, m, t, a, b, c, tmp;
	int z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 3;
	while(T--) {
		int n = 10000;
		set< pair<int, int> > S;
		printf("%d\n", n);
		for (int i = 0; i < n; i++) {
			int x, y;
			do {
				x = rand() * rand() %30000, y = rand() * rand() %30000;
				if (S.find(make_pair(x, y)) == S.end())
					break;
			} while (true);
			printf("%d %d\n", x, y);
			S.insert(make_pair(x, y));
		}
		if (T)	puts("");
	}
	return 0;
}
/*
20
5 0
8 2
4 5
5 8
9 5
0 8
6 0
2 0
7 7
6 3
0 0
1 7
7 4
0 9
9 8
9 2
7 2
2 7
0 0
6 0
*/
