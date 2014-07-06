#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;
struct E {
    int x, y, v;
    E(int a=0, int b=0, int c=0):
        x(a), y(b), v(c) {}
    bool operator<(const E &a) const {
        return  v < a.v;
    }
};
E D[100005];
vector<E> tree[3005];
int p[3005], rank[3005];
int findp(int x) {
    return p[x] == x ? x : (p[x] = findp(p[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x == y)
        return 0;
    if(rank[x] > rank[y])
        rank[x] += rank[y], p[y] = x;
    else
        rank[y] += rank[x], p[x] = y;
    return 1;
}
int kruscal(int n, int m) {
    int sum = 0;
    
    sort(D, D+m);
    for(int i = 0; i <= n; i++) {
        p[i] = i, rank[i] = 1;
        tree[i].clear();
    }
    
    for(int i = 0; i < m; i++) {
        if(joint(D[i].x, D[i].y)) {
        	sum += D[i].v;
        	tree[D[i].x].push_back(E(D[i].x, D[i].y, D[i].v));
        	tree[D[i].y].push_back(E(D[i].y, D[i].x, D[i].v));
//        	printf("mmm %d %d %d\n", D[i].x, D[i].y, D[i].v);
        }
    }
    return sum;
}
int dp[4096][20], dpw[4096][20];
int treeLevel[4096], treePath[4096];
void dfs(int u, int p, int level) {
	treeLevel[u] = level, treePath[level] = u;	
	for(int i = 1; (1<<i) < level; i++) {
		dp[u][i] = max(dp[u][i-1], dp[dpw[u][i-1]][i-1]);
		dpw[u][i] = treePath[level-(1<<i)];
	}
	for(int i = 0; i < tree[u].size(); i++) {
		int v = tree[u][i].y;
		if(v == p)	continue;		
		dp[v][0] = tree[u][i].v;
		dpw[v][0] = u;
		dfs(v, u, level + 1);
	}
}
int query(int x, int y) {
	int hx = treeLevel[x], hy = treeLevel[y];
	int ret = 0;
	while(x != y && hx != hy) {
		for(int i = 15; i >= 0; i--) {
			if(abs(hx-hy) >= (1<<i)) {
				if(hx > hy) {
					ret = max(ret, dp[x][i]);
					x = dpw[x][i];
					hx -= (1<<i);
				} else {
					ret = max(ret, dp[y][i]);
					y = dpw[y][i];
					hy -= (1<<i); 
				}
			}
		}
	}
	while(x != y) {
		ret = max(ret, dp[x][0]);
		x = dpw[x][0];
		hx -= (1<<0);
		ret = max(ret, dp[y][0]);
		y = dpw[y][0];
		hy -= (1<<0); 
	}
	return ret;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
        int n, m, q, x, y;

        scanf("%d %d", &n, &m);
        for(int i = 0; i < m; i++) {
        	scanf("%d %d %d", &D[i].x, &D[i].y, &D[i].v);        	
        }
        
		int mstcost = kruscal(n, m);
		memset(dp, 0, sizeof(dp));
		memset(dpw, 0, sizeof(dpw));
		dfs(1, -1, 1);
		
//		for(int i = 1; i <= n; i++, puts("")) {
//			printf("[%2d] :", i);
//			for(int j = 0; (1<<j) <= n; j++)
//				printf("%d %d, ", dp[i][j], dpw[i][j]);
//		}
		scanf("%d", &q);
		printf("Case %d\n", ++cases);
		while(q--) {
			scanf("%d %d", &x, &y);
			printf("%d\n", query(x, y));
		}
		puts("");
	}
    return 0;
}
/*
5
10 45
1 2 15
1 3 11
1 4 48
1 5 24
1 6 45
1 7 18
1 8 12
1 9 40
1 10 11
2 3 4
2 4 9
2 5 44
2 6 23
2 7 39
2 8 48
2 9 48
2 10 22
3 4 42
3 5 37
3 6 10
3 7 18
3 8 29
3 9 8
3 10 47
4 5 7
4 6 17
4 7 25
4 8 23
4 9 32
4 10 27
5 6 26
5 7 21
5 8 38
5 9 40
5 10 39
6 7 35
6 8 11
6 9 39
6 10 1
7 8 15
7 9 10
7 10 47
8 9 28
8 10 11
9 10 1
30
1 6

5
10 45
1 2 9
1 3 12
1 4 21
1 5 4
1 6 32
1 7 20
1 8 14
1 9 28
1 10 16
2 3 12
2 4 23
2 5 27
2 6 34
2 7 43
2 8 2
2 9 33
2 10 35
3 4 41
3 5 26
3 6 16
3 7 39
3 8 2
3 9 49
3 10 44
4 5 24
4 6 2
4 7 17
4 8 26
4 9 20
4 10 2
5 6 23
5 7 5
5 8 41
5 9 12
5 10 15
6 7 48
6 8 45
6 9 13
6 10 28
7 8 25
7 9 12
7 10 37
8 9 4
8 10 5
9 10 41
30
5 4
1 7
8 4
*/
