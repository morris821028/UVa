#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
const double pi = acos(-1);
const double eps = 1e-8;
int main() {
	int n, m, cases = 0;
	pair<int, int> A[MAXN];
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0, px = 0, py = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			A[i] = {x-px, y-py};
			px = x, py = y;
		}
		
		printf("Case %d: ", ++cases);
		int inc = 1;
		for (int i = 0; i < n; i++)
			inc &= A[i].first >= 0;
		if (m == 0 || inc == 1) {
			puts("Acceptable as proposed\n");	// Sample Ouput on UVa is wrong.
			continue;
		}
		
		pair<double, double> L, R;
		L = {0, pi}, R = {0, pi};
		for (int i = 0; i < n; i++) {
			if (A[i].first == 0 && A[i].second == 0)
				continue;
			double theta = atan2(A[i].second, A[i].first);
			if (theta >= -pi/2 && theta <= pi/2) {
				L.second = min(L.second, pi/2-theta);
				R.second = min(R.second, pi/2+theta);
			} else {
				if (theta <= 0) {
					L.first = max(L.first, -pi/2-theta);
					R.first = max(R.first,  pi/2+theta+pi);
				} else {
					L.first = max(L.first,  pi/2-theta+pi);
					R.first = max(R.first, -pi/2+theta);
				}
			}
		}

		if (L.first > L.second+eps && R.first > R.second+eps) {
			puts("Unacceptable");
		} else {
			double a = L.first;
			double b = R.first;
			if (L.first > L.second+eps)
				a = 2*pi;
			if (R.first > R.second+eps)
				b = 2*pi;
			if (a + eps < b)
				printf("Acceptable after counterclockwise rotation of %.2lf degrees\n", a*180/pi);
			else
				printf("Acceptable after clockwise rotation of %.2lf degrees\n", b*180/pi);
		}
		puts("");
	}
	return 0;
}
/*
1 1
0 1

1 1
1 0

2 45
10 10
0 1

2 0
1 1
2 0

3 45
10 10
1 10
5 6

0 0
*/
