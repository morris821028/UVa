#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105; 
const int INF = 0x1f3f3f3f;
int N, K, M, S, T;
int C[MAXN], A[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN];
int path[MAXN], used[MAXN];
void dfs(int idx, int u, int len, int &ret) {
	if (len >= ret)	return ;
	if (u == T) {
		ret = len;
		return ;
	}
	
	for (int i = 1; i <= N; i++) {
		if (!used[i] && len + g[u][i] + f[u][i] < ret) {
			used[i]++;
			path[idx] = i;
			for (int j = 1; j <= N; j++) {
				if (A[C[j]][C[i]])
					used[j]++;
			}
			dfs(idx+1, i, len + g[u][i], ret);
			for (int j = 1; j <= N; j++) {
				if (A[C[j]][C[i]])
					used[j]--;
			}
			used[i]--;
		}
	}
}
int main() {
	scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			f[i][j] = INF;
		f[i][i] = 0;
	}
	for (int i = 1; i <= N; i++)
		scanf("%d", &C[i]);
	for (int i = 1; i <= K; i++)
		for (int j = 1; j <= K; j++)
			scanf("%d", &A[i][j]);
	for (int i = 0; i < M; i++) {
		int u, v, d;
		scanf("%d %d %d", &u, &v, &d);
		if (!A[C[v]][C[u]])
			f[u][v] = min(f[u][v], d);
		if (!A[C[u]][C[v]])
			f[v][u] = min(f[v][u], d);
	}
	
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			g[i][j] = f[i][j];
	// floyd
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (!A[C[j]][C[i]] && !A[C[k]][C[i]] && !A[C[j]][C[k]])
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
	
	memset(used, 0, sizeof(used));
	int ret = INF;
	path[0] = S, used[S] = 1;
	for (int i = 1; i <= N; i++)
		if (A[C[i]][C[S]])
			used[i]++;
	if (f[S][T] != INF)
		dfs(1, S, 0, ret);
	printf("%d\n", ret == INF ? -1 : ret);
	return 0;
}
