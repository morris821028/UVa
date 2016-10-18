#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int CHARSET = 52;
static vector< pair<int, int> > g[MAXN][MAXN];
static int dp[MAXN][MAXN] = {};

void buildGraph(char S[], int sn, char T[], int tn) {
	static char node[MAXN][MAXN] = {};
	for (int i = 1; i <= sn; i++)
		memset(node[i], 0, sizeof(node[i]));
	int mx = dp[sn][tn];
	for (int i = 1; i <= sn; i++) {
		for (int j = 1; j <= tn; j++) {
			if (S[i] == T[j] && dp[i][j] == mx)
				node[i][j] = 1;
		}
	}
	for (int i = sn; i >= 1; i--) {
		for (int j = tn; j >= 1; j--) {
			if (node[i][j] == 0)
				continue;
			
			g[i][j].clear();
			int val = dp[i][j]-1;
			for (int p = 1; p < i; p++) {
				for (int q = 1; q < j; q++) {
					if (S[p] == T[q] && dp[p][q] == val) {
						g[i][j].push_back(make_pair(p, q));
						node[p][q] = 1;
					}
				}
			}
		}
	}
}
int countLCS(char S[], int sn, char T[], int tn) {
	int mx = dp[sn][tn];
	queue<int> X, Y;
	
	static int way[MAXN][MAXN], inq[MAXN][MAXN];
	for (int i = 1; i <= sn; i++) {
		for (int j = 1; j <= tn; j++) {
			way[i][j] = 0;
			inq[i][j] = 0;
			if (S[i] == T[j] && dp[i][j] == mx)
				X.push(i), Y.push(j), way[i][j] = 1, inq[i][j] = 1;
		}
	}
	
	int ret = 0;
	while (!X.empty()) {
		int x = X.front();
		int y = Y.front();
		int w = way[x][y];
		X.pop(), Y.pop();
		if (dp[x][y] == 1)
			ret += w;
		for (auto e: g[x][y]) {
			way[e.first][e.second] += w;
			if (!inq[e.first][e.second]) {
				inq[e.first][e.second] = 1;
				X.push(e.first), Y.push(e.second);
			}
		}
	}
	return ret;
}
void printLCS(char S[], int sn, char T[], int tn) {
	int mx = dp[sn][tn];
	struct State {
		int x, y, val;
		State(int x = 0, int y = 0, int val = 0):
			x(x), y(y), val(val) {}
	};
	static State stk[MAXN*MAXN];
	int stkIdx = 0;
	for (int i = 1; i <= sn; i++) {
		for (int j = 1; j <= tn; j++) {
			if (S[i] == T[j] && dp[i][j] == mx)
				stk[stkIdx] = State(i, j, dp[i][j]), stkIdx++;
		}
	}
	
	char path[MAXN];
	map<string, int> R;
	path[mx+1] = '\0';
	while (stkIdx) {
		State u = stk[--stkIdx];
		path[u.val] = T[u.y];
		if (u.val == 1) {
			R[path+1]++;
			continue;
		}
		for (auto e: g[u.x][u.y]) {
			stk[stkIdx] = State(e.first, e.second, u.val-1), stkIdx++;
		}
	}
	for (auto e : R) {
		for (int i = e.second-1; i >= 0; i--) {
			puts(e.first.c_str());
		}
	}

}
void run(char S[], char T[]) {
	int sn = strlen(S);
	int tn = strlen(T);

	S--, T--;

	for (int i = 1; i <= sn; i++)
		memset(dp[i], 0, sizeof(dp[i]));
	for (int i = 1; i <= sn; i++) {
		for (int j = 1; j <= tn; j++) {
			if (S[i] == T[j])
				dp[i][j] = dp[i-1][j-1]+1;
			else
				dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
		}
	}

	buildGraph(S, sn, T, tn);

	printf("%d %d\n", dp[sn][tn], countLCS(S, sn, T, tn));

	printLCS(S, sn, T, tn);
}

int main() {
	char S[MAXN], T[MAXN];
	while (scanf("%s", S) == 1) {
		assert(scanf("%s", T) == 1);
		run(S, T);
	}
	return 0;
}
/*
   PUWBVNUCUUESSJUNSVHE
   CIHSIIDWCSUTOSWJHTOB

   QHCCDETMFPPWZGIFEFUA
   GZXPAWWOOCZEMBIPHECM
 */

