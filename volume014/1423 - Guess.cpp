#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

int main() {
	int testcase, n;
	char s[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %s", &n, s);
		vector<int> g[16];
		int indeg[16] = {};
		for (int i = 1, k = 0; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				if (s[k] == '+') {
					g[i - 1].push_back(j);
					indeg[j]++;
				} else if (s[k] == '-') {
					g[j].push_back(i - 1);
					indeg[i - 1]++;
				}
				k++;
			}
		}
		
		queue<int> Q;
		for (int i = 0; i <= n; i++)
			if (indeg[i] == 0)
				Q.push(i);
		int prefixSum[16], val = 0;
		int u, v;
		while (!Q.empty()) {
			queue<int> R;
			while (!Q.empty()) {
				u = Q.front(), Q.pop();
				prefixSum[u] = val;
				R.push(u);
			}
			while (!R.empty()) {
				u = R.front(), R.pop();
				for (int i = 0; i < g[u].size(); i++) {
					v = g[u][i];
					if (--indeg[v] == 0)
						Q.push(v);
				}
			}
			val++;
		}
		for (int i = 1; i <= n; i++)
			printf("%d%c", prefixSum[i] - prefixSum[i-1], i == n ? '\n' : ' ');
	}
	return 0;
}
/*
3 
4 
-+0++++--+ 
2 
+++ 
5 
++0+-+-+--+-+--
*/
