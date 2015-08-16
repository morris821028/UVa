#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 300;
int main() {
	int testcase, N, x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &N);
		vector< pair<int, pair<int, int> > > A;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &x);
				A.push_back(make_pair(x, make_pair(i, j)));
			}
		}
		sort(A.begin(), A.end());
		int mx[MAXN] = {}, my[MAXN] = {};
		long long ret = 0;
		for (int i = A.size()-1; i >= 0; i--) {
			if (!mx[A[i].second.first] && !my[A[i].second.second]) {
				mx[A[i].second.first] = my[A[i].second.second] = 1;
				ret += A[i].first;
			}
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
2
3
100 120 50
0 90 70
20 40 80
2
1 2
3 4
*/
