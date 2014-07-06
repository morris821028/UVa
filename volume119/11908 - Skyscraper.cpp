#include <stdio.h>
#include <queue>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
struct adv {
	int l, r, v;
	adv(int a = 0, int b = 0, int c = 0):
		l(a), r(b), v(c) {}
	bool operator<(const adv &x) const {
		return make_pair(l, r) < make_pair(x.l, x.r);
	}
};
int main() {
	int testcase, cases = 0, n, A, B, C;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		vector<adv> D;
		for(int i = 0; i < n; i++) {
			scanf("%d %d %d", &A, &B, &C);
			D.push_back(adv(A, A+B, C));
		}
		sort(D.begin(), D.end());
		
		priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pQ;
		int prev = 0, ret = 0;
		for(int i = 0; i < n; i++) {
			while(!pQ.empty() && pQ.top().first <= D[i].l) {
				prev = max(prev, pQ.top().second);
				pQ.pop();
			}
			ret = max(ret, prev + D[i].v);
			pQ.push(make_pair(D[i].r, prev + D[i].v));
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
