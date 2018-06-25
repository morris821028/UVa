#include <bits/stdc++.h> 
using namespace std;

int main() {
	int n, w, u, v, t1, t2;
	while (scanf("%d %d %d %d %d %d", &n, &w, &u, &v, &t1, &t2) == 6) {
		vector<pair<double, int>> A;
		A.push_back({t1, 0});
		A.push_back({t2, 0});
		for (int i = 0; i < n; i++) {
			int m; char s[128];
			scanf("%s %d", s, &m);
			for (int j = 0; j < m; j++) {
				int l, pos;
				scanf("%d %d", &l, &pos);
				if (s[0] == 'E')
					pos = -pos;
				double tl, tr;
				tl = (double) pos / u - (double) w*(i+1) / v;
				tr = (double) (pos + l) / u - (double) w*i / v;
				A.push_back({tl, 1});
				A.push_back({tr, -1});
			}
		}

		sort(A.begin(), A.end());
		double ret = 0;
		int sum = 0;
		for (int i = 0; i < A.size(); i++) {
			sum += A[i].second;
			if (sum == 0 && A[i].first >= t1 && A[i].first < t2) {
				ret = max(ret, A[i+1].first - A[i].first);
			}
		}
		printf("%.8lf\n", ret);
	}
	return 0;
}
/*
3 100 5 10 0 100
E 2 100 -300 50 -100
W 3 10 60 50 200 200 400
E 1 100 -300
1 100 5 10 0 200
W 4 100 100 100 300 100 700 100 900
*/
