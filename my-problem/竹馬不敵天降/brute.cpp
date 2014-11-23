// Monte Carlo method 
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;
double mrandom() {
	int r = rand();
	return (double) r / RAND_MAX;
}
#define eps 1e-4
bool cmp(pair<double, int> a, pair<double, int> b) {
	if (fabs(a.first - b.first) > eps)
		return a.first > b.first;
	return a.second < b.second;
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("bruteout.txt", "w+t", stdout);
	int n, a, b;
	int cases = 0;
	int x[100], y[100];
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d %d", &a, &b);
		const int runtime = 3000000;
		for (int i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);
		int count[100] = {}, guess = runtime / n;
		double tx, ty, tz;
		for (int i = guess - 1; i >= 0; i--) {
			tx = mrandom() * a, ty = mrandom() * b;
			double dist = 1e+60, tmp;
			int mn = 0;
			for (int j = 0; j < n; j++) {
				tmp = (tx - x[j]) * (tx - x[j]) + (ty - y[j]) * (ty - y[j]);
				if (tmp < dist)
					dist = tmp, mn = j;
			}
			count[mn]++;
		}
		vector< pair<double, int> > ret;
		for (int i = 0; i < n; i++) 
			ret.push_back(make_pair((double)count[i] / guess, i));
		sort(ret.begin(), ret.end(), cmp);
		printf("Case %d:", ++cases);
		for (int i = 0; i < ret.size(); i++)
			printf(" %d", ret[i].second + 1);
		puts("");
	}
	return 0;
}
