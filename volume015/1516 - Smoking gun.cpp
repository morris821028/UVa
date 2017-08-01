#include <bits/stdc++.h>
using namespace std;

double dist(pair<int, int> p, pair<int, int> q) {
	return hypot(p.first-q.first, p.second-q.second);
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);
		const int MAXN = 128;
		pair<int, int> P[MAXN];
		map<string, int> R;
		vector<string> S;
		
		for (int i = 0; i < n; i++) {
			char s[32];
			int x, y;
			scanf("%s %d %d", s, &x, &y);
			P[i] = make_pair(x, y);
			R[s] = i;
			S.push_back(s);
		}
		
		double f[MAXN][MAXN];
		int has[MAXN] = {};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				f[i][j] = 1e+30;
		}
		
		for (int i = 0; i < m; i++) {
			char s1[32], s2[32], s3[32];
			scanf("%s %*s %s %*s %*s %s", s1, s2, s3);
			int o = R[s1], u = R[s2], v = R[s3];
			has[u] = has[v] = 1;
			f[u][v] = min(f[u][v], dist(P[v], P[o])-dist(P[u], P[o]));
			// make dist(u, v) > dist(P[u], P[o])-dist(P[v], P[o])
		}
		
		// floyd algorithm
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
					f[i][j] = min(f[i][j], f[i][k]+f[k][j]);
			}
		}
		
		// check negative cycle exists
		int neg = 0;
		for (int i = 0; i < n; i++)
			neg |= f[i][i] < 0;
			
		if (neg) {
			puts("IMPOSSIBLE");
			continue;
		}
		
		// topological
		{
			int err = 0;
			int m = 0;
			for (int i = 0; i < n; i++)
				m += has[i];
			vector<string> ret;
			for (int it = 0; it < m; it++) {
				int out = 0, out_i;
				for (int i = 0; i < n; i++) {
					if (!has[i])
						continue;
					int indeg = 0;
					for (int j = 0; j < n; j++) {
						if (!has[j] || i == j)
							continue;
						if (f[i][j] >= 0)
							indeg++;
					}
					if (indeg == 0) {
						out++;
						out_i = i;
						break;
					}
				}
				if (out != 1) {
					err = 1;
					break;
				}
				has[out_i] = 0;
				ret.push_back(S[out_i]);
			}
			
			if (err) {
				puts("UNKNOWN");
			} else {
				for (int i = 0; i < ret.size(); i++)
					printf("%s%c", ret[i].c_str(), " \n"[i==ret.size()-1]);
			}
		}		
	}
	return 0;
}
/*
3
4 2
BillyTheKid 0 0
Andy 10 0
John 19 0
Larry 20 0
Andy heard BillyTheKid firing before John
Larry heard John firing before BillyTheKid
2 2
Andy 0 0
Beate 0 1
Andy heard Beate firing before Andy
Beate heard Andy firing before Beate
3 1
Andy 0 0
Beate 0 1
Charles 1 3
Beate heard Andy firing before Charles
*/
