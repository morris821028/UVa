#include <stdio.h>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;
struct cmp {
	bool operator() (const pair<int, int> &x, const pair<int, int> &y) {
		return x > y;
	}
};
int main() {
	int n, cases = 0, x, y;
	while(scanf("%d", &n) == 1 && n != -1) {
		vector< pair<int, int> > D;
		for(int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			D.push_back(make_pair(x, y));
		}
		sort(D.begin(), D.end());
		int ret = 0;
		priority_queue<int, vector<int>, greater<int> > pQ;
		for(int i = 0; i < n; i++) {
			while(!pQ.empty() && pQ.top() < D[i].first)
				pQ.pop();
			pQ.push(D[i].second);
			ret = max(ret, (int)pQ.size());
		}	
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
