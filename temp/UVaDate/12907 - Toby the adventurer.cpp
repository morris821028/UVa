#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 10005;
const int MAXM = MAXN * 32;
struct Node {
    int x, y;
    int v;// x->y, v
    int next;
} edge[MAXM];
int e, g[MAXN];// direct graph record
int visited[MAXN];
void addEdge(int x, int y, int v) {
    if(x == y)    return;
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = g[x], g[x] = e++;
}
void dfs(int x) {
    visited[x] = 1;
    for (int i = g[x]; i != -1; i = edge[i].next) {
        if (!visited[edge[i].y])
            dfs(edge[i].y);
    }
}
int testDMSTsolvable(int root, int n) { //node [0, n-1]   
    for (int i = 0; i < n; i++)
    	visited[i] = 0;
    dfs(root);
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0)
            return 0;
    }
    return 1;
}
void initGraph(int n) {
	e = 0;
	for (int i = 0; i < n; i++)
		g[i] = -1;
}

//
int n, m, root, U[MAXN], V[MAXN], W[MAXN], eIdx[MAXN], indeg[MAXN];
bool cmp(int x, int y) {
	return W[x] > W[y];
}
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d %d", &n, &m, &root);
        
        initGraph(n);
        for (int i = 0; i < n; i++)
        	indeg[i] = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &U[i], &V[i], &W[i]);
            addEdge(U[i], V[i], W[i]);
            indeg[V[i]]++;
        }
        
        if (!testDMSTsolvable(root, n)) {
        	puts("impossible");	
        } else {
        	for (int i = 0; i < m; i++)
        		eIdx[i] = i;
        	sort(eIdx, eIdx+m, cmp);
        	
        	if (m == n-1) {
        		long long cost = 0;
        		for (int i = 0; i < m; i++)
        		    cost += W[eIdx[i]];
        		    
        		printf("%lld\n", cost);
        		for (int i = 0; i < m; i++)
        			printf("%d %d %d\n", U[eIdx[i]], V[eIdx[i]], W[eIdx[i]]);
        		continue;
        	}
        	
        	for (int i = 0; i < m; i++) {
        		if (indeg[V[eIdx[i]]] == 1)
        			continue;
        			
        		initGraph(n);
        		long long cost = 0;
        		for (int j = 0; j < m; j++) {
        			if (i == j)	
						continue;
        			addEdge(U[eIdx[j]], V[eIdx[j]], W[eIdx[j]]);
        			cost += W[eIdx[j]];
        		}
        		
        		if (testDMSTsolvable(root, n)) {
        			printf("%lld\n", cost);
        			for (int j = 0; j < m; j++) {
        				if (i == j)	
							continue;
						printf("%d %d %d\n", U[eIdx[j]], V[eIdx[j]], W[eIdx[j]]);
        			}
        			break;
        		}
        	}
        }
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
