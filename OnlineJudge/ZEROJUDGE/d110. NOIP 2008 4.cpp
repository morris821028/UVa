#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 1024;
int n, A[MAXN], color[MAXN];
vector<int> g[MAXN];

int dfs(int u, int c) {
	color[u] = c;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (color[v] == -1) {
			if (dfs(v, 1-c))
				return 1;
		}
		if (color[v] == color[u])
			return 1;
	}
	return 0;
}
void solve() {
	for (int i = 1; i <= n; i++)
		color[i] = -1;
	for (int i = 1; i <= n; i++) {
		if (color[i] == -1) {
			if (dfs(i, 0)) {
				puts("0");
				return ;
			}
		}
	}
	
	int val = 1;
	stack<int> stk1, stk2;
	for (int i = 0; i < n; i++) {
		int x = A[i];
		if (color[x] == 0) {
			stk1.push(x), printf("a ");
		} 
		if (color[x] == 1) {
			stk2.push(x), printf("c ");
		}
		while (true) {
			if (!stk1.empty() && stk1.top() == val) {
				stk1.pop(), val++;
				printf("b ");
			} else if (!stk2.empty() && stk2.top() == val) {
				stk2.pop(), val++;
				printf("d ");
			} else {
				break;
			}
		}
	}
	puts("");
}
int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
			
		for (int i = 0; i < n; i++)
			g[i].clear();
		int B[MAXN];
		B[n] = INT_MAX;
		for (int i = n-1; i >= 0; i--)
			B[i] = min(B[i+1], A[i]);
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				if (A[i] < A[j] && B[j+1] < A[i]) {
					g[A[i]].push_back(A[j]);
					g[A[j]].push_back(A[i]);
				}
			}
		}
		solve();
	}
	return 0;
}
