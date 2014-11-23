#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
struct Rectangle {
	int lx, ly, rx, ry;
	void read() {
		scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
	}
	int contain(Rectangle &a) {
		return lx <= a.lx && ly <= a.ly && rx >= a.rx && ry >= a.ry;
	}
	int contain(int x, int y) {
		return lx <= x && ly <= y && rx >= x && ry >= y;
	}
} rect[32767];
struct QPt {
	int x, y, label;
	QPt(int a = 0, int b = 0, int c = 0):
		x(a), y(b), label(c) {}
	bool operator<(const QPt &a) const {
		return make_pair(x, y) < make_pair(a.x, a.y);
	}
};
vector<int> g[32767];
int parent[32767], visited[32767], depth[32767];
void dfs(int u) {
	visited[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (visited[v] == 0) {
			if (rect[u].contain(rect[v]))
				parent[v] = u, depth[v] = depth[u] + 1;
			else
				parent[v] = parent[u], depth[v] = depth[parent[u]] + 1;
			dfs(v);
		}
	}
}
int main() {	
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, m, x, y;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			rect[i].read(), g[i].clear(), visited[i] = 0;
		scanf("%d", &m);
		vector<QPt> XY;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			XY.push_back(QPt(x, y, i));
		}
		map<int, vector< pair<int, int> > > R;
		for (int i = 0; i < n; i++) {
			vector< pair<int, int> > &l = R[rect[i].lx], &r = R[rect[i].rx];
			l.push_back(make_pair(i, 1));
			l.push_back(make_pair(i, 2));
			r.push_back(make_pair(i, -1));
			r.push_back(make_pair(i, -2));
		}
		set< pair<int, int> > S;
		set< pair<int, int> >::iterator Sit, Sjt;
		for (map<int, vector< pair<int, int> > >::iterator it = R.begin();
			it != R.end(); it++) {
			vector< pair<int, int> > &D = it->second;
			for (int i = 0; i < D.size(); i++) {
				int k = D[i].first;
				if (D[i].second > 0) {
					if (D[i].second == 1) {
						Sit = S.lower_bound(make_pair(rect[k].ly, -1)), Sjt = Sit;
						if (Sit != S.begin()) {
							Sjt--;
							g[Sjt->second].push_back(k);
						}
						S.insert(make_pair(rect[k].ly, k));
					} else {
						Sit = S.lower_bound(make_pair(rect[k].ry, -1)), Sjt = Sit;
						if (Sit != S.end()) {
							g[Sit->second].push_back(k);
						}
						S.insert(make_pair(rect[k].ry, k));
					}
				} else {
					if (D[i].second == -1)	S.erase(make_pair(rect[k].ly, k));
					else					S.erase(make_pair(rect[k].ry, k));
				}
			}
		}
		int indeg[32767] = {};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < g[i].size(); j++)
				indeg[g[i][j]]++;
		}
		for (int i = 0; i < n; i++) {
			if (indeg[i] == 0) {
				parent[i] = -1, depth[i] = 1;
				dfs(i);
			}
		}
		for (int i = 0; i < n; i++)
			printf("%d%c", depth[i], i == n - 1 ? '\n' : ' ');
			
		sort(XY.begin(), XY.end());		
		int run_m = 0, OUT[32767] = {};
		S.clear();
		for (map<int, vector< pair<int, int> > >::iterator it = R.begin();
			it != R.end(); it++) {					
			vector< pair<int, int> > &D = it->second;
			for (int i = 0; i < D.size(); i++) {
				int k = D[i].first;
				if (D[i].second > 0) {
					if (D[i].second == 1) {
						Sit = S.lower_bound(make_pair(rect[k].ly, -1)), Sjt = Sit;
						S.insert(make_pair(rect[k].ly, k));
					} else {
						Sit = S.lower_bound(make_pair(rect[k].ry, -1)), Sjt = Sit;
						S.insert(make_pair(rect[k].ry, k));
					}
				}
			}			
			while (run_m < m && XY[run_m].x <= it->first) {
				Sit = S.lower_bound(make_pair(XY[run_m].y, -1));
				if (rect[Sit->second].contain(XY[run_m].x, XY[run_m].y))
					OUT[XY[run_m].label] = Sit->second;
				else
					OUT[XY[run_m].label] = parent[Sit->second];
				run_m++;
			}
			for (int i = 0; i < D.size(); i++) {
				int k = D[i].first;
				if (D[i].second < 0) {
					if (D[i].second == -1)	S.erase(make_pair(rect[k].ly, k));
					else					S.erase(make_pair(rect[k].ry, k));
				}
			}
		}
		for (int i = 0; i < m; i++)
			printf("%d\n", OUT[i]);
	}
	return 0;
}
/*
7
0 0 10 10
1 1 9 2
1 3 9 7
2 4 4 6
5 4 6 5
7 5 8 6
1 8 9 9 
6 
3 5
6 6
7 4
9 1 
2 4 
-1 -1 
*/ 
