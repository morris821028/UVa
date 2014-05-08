#include <stdio.h>
#include <vector>
#include <string.h>
#include <math.h>
using namespace std;
struct Node {
    int x, y;
    int v;// x->y, v
    int next;
} edge[65536];
int e, g[128], vg[128];// direct graph record
void addEdge(int x, int y, int v) {
    if(x == y)    return;
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = g[x], g[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].v = -127;//this weight not important.
    edge[e].next = vg[y], vg[y] = e++;
}
int visited[1005];
void dfs(int x) {
    visited[x] = 1;
    for(int i = g[x]; i != -1; i = edge[i].next) {
        if(!visited[edge[i].y])
            dfs(edge[i].y);
    }
}
double mst(int root, int n) {//node [0, n-1]
#define oo 1000000000
    int i, j, k;
    int u;
    int v;
    memset(visited, 0, sizeof(visited));
    dfs(root);
    for(i = 0; i < n; i++)
        if(visited[i] == 0)
            return -1;
    // solvable
    int prev[128], dele[128];
    int ret = 0;
    int vprev[128];
    int in[128], out[128];
    memset(dele, 0, sizeof(dele));
    while(true) {
        for(i = 0; i < n; i++)
            prev[i] = i, vprev[i] = oo;
        for(i = 0; i < n; i++) {// O(E)
            if(dele[i])
                continue;
            for(j = g[i]; j != -1; j = edge[j].next) {
                u = edge[j].y, v = edge[j].v;
                if(dele[u])
                    continue;
                if(vprev[u] > v)
                    vprev[u] = v, prev[u] = i;
            }
        }
        for(i = 0; i < n; i++) {
            if(dele[i] || i == root)
                continue;
            j = i; // find cycle
            memset(visited, 0, sizeof(visited));
            visited[root] = 1;
            do visited[j] = 1, j = prev[j];
            while(!visited[j]);
            if(j == root)    continue;
            i = j;
            ret += vprev[i];
            for(j = prev[i]; j != i; j = prev[j]) {
                ret += vprev[j];
                dele[j] = 1;
            }
            // modify edge weight.
            //printf("modify edge weight\n");
            for(j = vg[i]; j != -1; j = edge[j].next) {
                u = edge[j].y;// u->i
                if(dele[u])
                    continue;
                edge[j^1].v -= vprev[i];
            }
            for(k = 0; k < n; k++)
                in[k] = oo, out[k] = oo;
            for(j = prev[i]; j != i; j = prev[j]) {
                for(k = vg[j]; k != -1; k = edge[k].next) {
                    u = edge[k].y, v = edge[k^1].v;// u->cycle
                    if(dele[u])
                        continue;
                    v -= vprev[j];
                    in[u] = min(in[u], v);
                }
                for(k = g[j]; k != -1; k = edge[k].next) {
                    u = edge[k].y, v = edge[k].v;// cycle->u
                    if(dele[u])
                        continue;
                    out[u] = min(out[u], v);
                }
            }
            for(k = 0; k < n; k++) {
                if(k == i)
                    continue;
                if(in[k] != oo)
                    addEdge(k, i, in[k]);
                if(out[k] != oo)
                    addEdge(i, k, out[k]);
            }
            break;// repeat for a new graph.
        }
        if(i == n) {// there not exist cycle.
            for(i = 0; i < n; i++) {
                if(dele[i] || i == root)
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
    int i, j, k, u[10005], v[10005], b[10005], c[10005];
    int testcase;
    int cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
        int n, m, o;
        scanf("%d %d %d", &n, &m, &o);
        int l = 0, r = 0, mid;
        for(i = 0; i < m; i++) {
        	scanf("%d %d %d %d", &u[i], &v[i], &b[i], &c[i]);
        	r = max(r, b[i]);
        }
        int ret = -1;
        while(l <= r) {
        	mid = (l + r)/2;
        	e = 0;
        	memset(g, -1, sizeof(g));
        	memset(vg, -1, sizeof(vg));
        	for(i = 0; i < m; i++) {
        		if(b[i] >= mid)
        			addEdge(u[i], v[i], c[i]);
        	}
        	int f = mst(0, n);
        	if(f != -1 && f <= o)
        		l = mid + 1, ret = mid;
        	else
        		r = mid - 1;
        }
        if(ret > 0)
        	printf("%d kbps\n", ret);
        else
        	printf("streaming not possible.\n");
    }
    return 0;
} 
