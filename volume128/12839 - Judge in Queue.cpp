#include <stdio.h>
#include <functional>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int A[131072];
int main() {
	int testcase, cases = 0, n, m, x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		sort(A, A+n, greater<int>());
		priority_queue< pair<long long, long long>, vector< pair<long long, long long> >, 
						greater< pair<long long, long long> > > pQ;
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			pQ.push(make_pair(0, x));
		}
		long long ret = 0;
		for (int i = 0; i < n; i++) {
			ret = max(ret, A[i] + pQ.top().first);
			pair<long long, long long> v = pQ.top();
			pQ.pop(), pQ.push(make_pair(v.first + v.second, v.second));
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
