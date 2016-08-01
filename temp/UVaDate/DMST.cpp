#include <stdio.h>
#include <vector>
#include <string.h>
#include <math.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = MAXN * 32;
struct Node {
    int x, y;
    int v;// x->y, v
    int next;
} edge[MAXM];
int e, g[MAXN], vg[MAXN];// direct graph record
int visited[MAXN];
void addEdge(int x, int y, int v) {
    if(x == y)    return;
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = g[x], g[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].v = -127;//this weight not important.
    edge[e].next = vg[y], vg[y] = e++;
}
void dfs(int x) {
    visited[x] = 1;
    for (int i = g[x]; i != -1; i = edge[i].next) {
        if (!visited[edge[i].y])
            dfs(edge[i].y);
    }
}
double mst(int root, int n) {//node [0, n-1]
#define oo 0x3f3f3f3f
    int i, j, k;
    int u, v;
    
    memset(visited, 0, sizeof(visited));
    dfs(root);
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0)
            return -1;
    }
    // solvable
    int prev[1005], dele[1005];
    int ret = 0;
    int vprev[1005];
    int in[1005], out[1005];
    
    memset(dele, 0, sizeof(dele));
    while (true) {
        for (int i = 0; i < n; i++)
            prev[i] = i, vprev[i] = oo;
            
        for (int i = 0; i < n; i++) {// O(E)
            if (dele[i])
                continue;
            for (int j = g[i]; j != -1; j = edge[j].next) {
                u = edge[j].y, v = edge[j].v;
                if (dele[u])
                    continue;
                if (vprev[u] > v)
                    vprev[u] = v, prev[u] = i;
            }
        }
        
        int hasCycle = 0;
        for (int i = 0; i < n && !hasCycle; i++) {
        	if(dele[i] || i == root)
                continue;
                
            int u = i; // find cycle
            memset(visited, 0, sizeof(visited));
            visited[root] = 1;
            do {
            	visited[u] = 1, u = prev[u];
            } while (!visited[u]);
            
            if	(u == root)
				continue;
			hasCycle = 1;
            i = u;
            ret += vprev[i];
            for (int j = prev[i]; j != i; j = prev[j]) {
                ret += vprev[j];
                dele[j] = 1;
            }
            // modify edge weight.
            //printf("modify edge weight\n");
            for (int j = vg[i]; j != -1; j = edge[j].next) {
                u = edge[j].y;// u->i
                if (dele[u])
                    continue;
                edge[j^1].v -= vprev[i];
            }
            for (int k = 0; k < n; k++)
                in[k] = oo, out[k] = oo;
            for (int j = prev[i]; j != i; j = prev[j]) {
                for (int k = vg[j]; k != -1; k = edge[k].next) {
                    u = edge[k].y, v = edge[k^1].v;// u->cycle
                    if (dele[u])
                        continue;
                    v -= vprev[j];
                    in[u] = min(in[u], v);
                }
                for (int k = g[j]; k != -1; k = edge[k].next) {
                    u = edge[k].y, v = edge[k].v;// cycle->u
                    if (dele[u])
                        continue;
                    out[u] = min(out[u], v);
                }
            }
            
            for (int k = 0; k < n; k++) {
                if (k == i)
                    continue;
                if (in[k] != oo)
                    addEdge(k, i, in[k]);
                if (out[k] != oo)
                    addEdge(i, k, out[k]);
            }
        }
        
        if (!hasCycle) {// there not exist cycle.
            for (int i = 0; i < n; i++) {
                if (dele[i] || i == root)
                    continue;
                //printf("%lf\n", vprev[i]);
                ret += vprev[i];
            }
            break;
        }
    }
    return ret;
}
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        int n, m, root;
        int i, j, k, u, v, w;
        scanf("%d %d %d", &n, &m, &root);
        e = 0;
        memset(g, -1, sizeof(g));
        memset(vg, -1, sizeof(vg));
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
        }
        
        int ret = mst(root, n);
        if (ret < 0)
            puts("Possums!");
        else
            printf("%d\n", ret);
    }
    return 0;
} 
/*
2

5 5 0
0 1 1
0 2 100
1 3 2
3 2 3
2 4 4

5 5 4
0 1 1
0 2 100
1 3 2
3 2 3
2 4 4
*/
