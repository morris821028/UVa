#include <stdio.h> 
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
vector< pair<int, int> > g[100005];
int dist[100005], used[100005], testcase = 0;
typedef pair<int, int> P;
struct cmp {
	bool operator() (const P a, const P b) const {
		if(a.first != b.first)
			return a.first > b.first;
		return a.second < b.second;
	}
}; 
int dijkstra(int st, int cutLength) {
	++testcase;
	priority_queue< P, vector<P>, cmp> pQ;
	dist[st] = 0, used[st] = testcase;
	pQ.push(make_pair(0, st));
	int ret = 0, u, w, ww;
	P f;
	int testi = st;
	while(!pQ.empty()) {
		f = pQ.top(), pQ.pop();
		st = f.second, ww = f.first;
		if(dist[st] < ww)	continue;
		for(int i = g[st].size() - 1; i >= 0; i--) {
			u = g[st][i].first, w = g[st][i].second;
			if(used[u] != testcase)	{
				used[u] = testcase;
				dist[u] = 0x3f3f3f3f;
			}
			if(dist[u] > cutLength && ww + w <= cutLength) {
				ret++;
			}
			if(dist[u] > ww + w && ww + w <= cutLength) {
				dist[u] = ww + w;
				pQ.push(make_pair(dist[u], u));
			}
		}
	}
	return ret;
}
int main() {
	int n, m, x, w;
	while(scanf("%d %d", &n, &m) == 2) {
		for(int i = 1; i <= n; i++)
			g[i].clear();
		for(int i = 1; i <= n; i++) {
			scanf("%d %d", &x, &w);
			g[x].push_back(make_pair(i, w));
			g[i].push_back(make_pair(x, w));
		}
		int ret = 0;
		for(int i = 1; i <= n; i++) {
			ret += dijkstra(i, m);
		}
		printf("%d\n", ret / 2);
	}
	return 0;
}
