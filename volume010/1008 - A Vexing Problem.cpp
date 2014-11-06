#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

#define hash_mod 1000003
int n, m, visited[16][16], cases = 0;
struct State {
	char g[10][10];
	int label;
	bool operator<(const State &x) const {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (g[i][j] != x.g[i][j])
					return g[i][j] < x.g[i][j];
		return false;
    }
	unsigned int hash() {
		unsigned int a = 63689, b = 378551;
		unsigned int value = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				value = value * a + g[i][j];
				a *= b;
			}
		}
		return value % hash_mod;
	}
	int dfs(int x, int y, char c) {
		if (x < 0 || y < 0 || x >= n || y >= m)
			return 0;
		if (g[x][y] != c || visited[x][y] == cases)
			return 0;
		visited[x][y] = cases;
		int ret = 0;
		ret += dfs(x+1, y, c);
		ret += dfs(x, y+1, c);
		ret += dfs(x-1, y, c);
		ret += dfs(x, y-1, c);
		return 1 + ret;
	}
	void erase(int x, int y, int c) {
		if (x < 0 || y < 0 || x >= n || y >= m)
			return ;
		if (g[x][y] != c || visited[x][y] != cases)
			return ;
		g[x][y] = '-';
		erase(x+1, y, c);
		erase(x, y+1, c);
		erase(x-1, y, c);
		erase(x, y-1, c);
	}
	void fall() {
		for (int i = n-1; i >= 0; i--) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] >= 'A' && g[i][j] <= 'Z') {
					int k = i+1;
					while (k < n && g[k][j] == '-') {
						g[k][j] = g[k-1][j];
						g[k-1][j] = '-';
						k++;
					}
				}
			}
		}
	}
	void refresh() {
		int update = 0, cnt;
		do {
			fall();
			update = 0;
			memset(visited, 0, sizeof(visited));
			cases = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (visited[i][j] == 0 && g[i][j] >= 'A' && g[i][j] <= 'Z') {
						cases++;
						cnt = dfs(i, j, g[i][j]);
						if (cnt > 1)
							erase(i, j, g[i][j]), update = 1;
					}
				}
			}
		} while (update);
	}
	int isCompleted() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				if (g[i][j] >= 'A' && g[i][j] <= 'Z')
					return 0;
		}
		return 1;
	}
};
struct Info {
	int x, y, dir, prev;
	char c;
	Info(int s1 = 0, int s2 = 0, int s3 = 0, int s4 = 0, char s = 0):
		x(s1), y(s2), dir(s3), prev(s4), c(s) {
	}
};
map<State, int> R[hash_mod];
vector<Info> history;
int main() {
	char casesName[105];
	State st, next;
	int h, step;
	while (scanf("%d %d %s", &n, &m, casesName) == 3 && n) {
		for (int i = 0; i < n; i++)
			scanf("%s", &st.g[i]);
		history.resize(1);
		for (int i = 0; i < hash_mod; i++)
			R[i].clear();
		
		int labelCnt = 0, label;
		queue<State> Q;
		st.refresh(), st.label = 0;		
		h = st.hash();
		R[h][st] = 0, Q.push(st);
		while (!Q.empty()) {
			st = Q.front(), Q.pop();
			h = st.hash(), label = st.label;
			step = R[h][st];
			if (st.isCompleted())
				break;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (st.g[i][j] >= 'A' && st.g[i][j] <= 'Z') {
						if (j+1 < m && st.g[i][j+1] == '-') {
							next = st;
							swap(next.g[i][j], next.g[i][j+1]);
							next.refresh();
							h = next.hash();
							if (R[h].find(next) == R[h].end()) {
								next.label = ++labelCnt;
								history.push_back(Info(i, j, 1, label, st.g[i][j]));
								R[h][next] = step + 1;
								Q.push(next);
							}
						}
						if (j-1 >= 0 && st.g[i][j-1] == '-') {
							next = st;
							swap(next.g[i][j], next.g[i][j-1]);
							next.refresh();
							h = next.hash();
							if (R[h].find(next) == R[h].end()) {
								next.label = ++labelCnt;
								history.push_back(Info(i, j, 0, label, st.g[i][j]));
								R[h][next] = step + 1;
								Q.push(next);
							}
						}
					}
				}
			}
		}
		printf("%s: Minimum solution length = %d\n", casesName, step);
		int idx = st.label;
		vector<Info> ret;
		while (idx) {
			ret.push_back(history[idx]);
			idx = history[idx].prev;
		}
		for (int i = ret.size() - 1, j = 0; i >= 0; i--, j++) {
			if (j%4)	putchar(' ');
			printf("(%c,%d,%d,%c)", ret[i].c, ret[i].x, ret[i].y, ret[i].dir ? 'R' : 'L');
			if (j%4 == 3)	puts("");
		}
		if (ret.size()%4)	puts("");
	}
	return 0;
}
