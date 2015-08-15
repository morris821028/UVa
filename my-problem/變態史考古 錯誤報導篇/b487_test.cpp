#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 131072;
int parent[MAXN], weight[MAXN];
void init(int n) {
    for(int i= 0; i <= n; i++)
        parent[i] = i, weight[i] = 1;
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y) return 0;
    if(weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}
int fa[MAXN], used[MAXN], pos[MAXN];
int main() {
	int n, m, x, y, c, u, v, cases = 0;
	char cmd[8];
	while (scanf("%d %d", &n, &m) == 2) {
		init(n);
		for (int i = 0; i <= n; i++)
			fa[i] = 0, used[i] = 0;
		cases = 0;
		for (int i = 0; i < m; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'n') {		// link
				scanf("%d %d", &x, &y);
				fa[x] = y;
			} else if (cmd[0] == 's') {	// sim
				scanf("%d %d", &x, &y);
				if (x == y) {
					puts("1/1");
					continue;
				} 
				cases++;
				int p1 = 0, p2 = 0, p3 = 0, lca = -1;
				for (int u = x; u; u = fa[u])
					used[u] = cases, pos[u] = p1, p1++;
				for (int u = y; u; u = fa[u]) {
					p2++;
					if (used[u] == cases) {
						p3 = p1 - pos[u];
						p2 += p3 - 1;
						lca = u;
						break;
					}
				}
				if (lca == -1)  {
					puts("-1");
					continue;
				}
//				printf("lca %d, %d %d %d\n", lca, p1, p2, p3);
				int a = p3 * 2, b = p1 + p2, g;
				g = __gcd(a, b), a /= g, b /= g;
				printf("%d/%d\n", a, b);
			}
		}
	}
	return 0;
}
/*
5 9
news 3 2
news 4 2
sim 3 4
sim 3 5
news 2 1
news 5 4
sim 3 4
sim 3 5
sim 4 4
*/
