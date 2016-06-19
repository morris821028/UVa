#include <bits/stdc++.h>
using namespace std;

double P[1024][512], V[1024];
bool cmp(pair<double, int> a, pair<double, int> b) {
	if (a.first != b.first)
		return a.first > b.first;
	return a.second < b.second;
}
int main() {
	int testcase, A, B;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &A, &B);
		double T[1024] = {}, tot = 0;
		int out[1024] = {};
		for (int i = 0; i < B; i++) {
			for (int j = 0; j < A; j++)
				scanf("%lf", &P[i][j]);
			scanf("%lf", &V[i]);
			tot += V[i];
			for (int j = 0; j < A; j++)
				T[j] += P[i][j] * V[i];
		}
		vector< pair<double, int> > O;
		for (int i = 0; i < A; i++) 
			O.push_back(make_pair(T[i], i+1));
		sort(O.begin(), O.end(), cmp);
		int ret = 2;
		if (O[0].first >= tot * 50.1)
			ret = 1;
		for (int i = 0; i < O.size() && i < ret; i++)
			printf("%d %.lf\n", O[i].second, O[i].first/100);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
3
4  3
25.0  25.0  25.0  25.0  4500
26.0  24.0  27.0  23.0  9000
10.0  10.0  10.0  70.0  1000
3  1
51.0  24.0  25.0  1000
2  2
0.7  99.3  2788000
99.3  0.7  2788000
*/
