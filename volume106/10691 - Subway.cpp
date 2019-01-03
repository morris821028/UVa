#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

bool cmp(pair<double, double> a, pair<double, double> b) {
	return a.second < b.second;
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, d;
		scanf("%d %d", &n, &d);
		vector<pair<double, double>> A;
		for (int i = 0; i < n; i++) {
			double x, y;
			scanf("%lf %lf", &x, &y);
			double dist = sqrt(x*x + y*y);
			if (dist <= d)
				continue;
			double theta = atan2(y, x);
			double delta = asin(d / dist);
			double l = theta - delta;
			double r = theta + delta;
			if (r > pi)	l -= 2*pi, r -= 2*pi;
			A.push_back({l, r});
		}

		sort(A.begin(), A.end(), cmp);
		n = A.size();
		int ret = n;
		for (int i = 0; i < n; i++)
			A.push_back({A[i].first + 2*pi, A[i].second + 2*pi});

		for (int i = 0; i < n; i++) {
			int cnt = 1;
			double r = A[i].second;
			for (int j = i+1; j < i+n; j++) {
				if (r < A[j].first - 1e-9) {
					cnt++;
					r = A[j].second;
				}
			}
			ret = min(ret, cnt);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2
7 1
-1 -4
-3 1
-3 -1
2 3
2 4
2 -2
6 -2

4 0
0 4
-12 18
0 27
-34 51


2
1 55
1 1
1 0
3 5
*/
