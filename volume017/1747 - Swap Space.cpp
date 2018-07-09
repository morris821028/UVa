#include <bits/stdc++.h> 
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		vector<pair<int, pair<int, int>>> A;
		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (b > a)
				A.push_back({a, {a, b}});
			else
				A.push_back({INT_MAX-b, {a, b}});
		}
		
		sort(A.begin(), A.end());
		int64_t ret = 0;
		int64_t available = 0;
		for (int i = 0; i < n; i++) {
			if (available < A[i].second.first) {
				ret += A[i].second.first - available;
				available = A[i].second.first;
			}
			available += A[i].second.second - A[i].second.first;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
4
6  6
1  7
3  5
3  5
4
2  2
3  3
5  1
5  10
*/
