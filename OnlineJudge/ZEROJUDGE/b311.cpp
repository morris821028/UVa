#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.first + b.first + b.second * a.first <
			b.first + a.first + a.second * b.first;
}
const unsigned long long mod = 100000007ULL;
void brute(int n, vector< pair<int, int> > D) {
	int A[16];
	for (int i = 0; i < n; i++)
		A[i] = i;
	double ret = 1ULL<<60;
	do {
		double time = 0;
		for (int i = 0; i < n; i++) {
			time = (time + D[A[i]].first + D[A[i]].second * time);
		}
		ret = min(ret, time);
	} while (next_permutation(A, A+n));
	printf("%lf\n", ret);
}
int main() {
	int n, x, y;
	while (scanf("%d", &n) == 1) {
		vector< pair<int, int> > D;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			D.push_back(make_pair(x, y));
		}
		sort(D.begin(), D.end(), cmp);
		unsigned long long time = 0;
		for (int i = 0; i < n; i++) {
			time = (time + D[i].first + D[i].second * time %mod) %mod;
		}
		printf("%llu\n", time);
		brute(n, D);
	} 
	return 0;
}
/*
10
0 0
5 6
2 10
3 8
4 5
2 0
0 7
12 8
9 9
9 9
*/
