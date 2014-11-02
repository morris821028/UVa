#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
using namespace std;
#define maxL (500000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[1048576], Pt = 0;
void sieve() {
	register int i, j, k;
	SET(1);
	int n = 500000;
	for(i = 2; i <= n; i++) {
		if(!GET(i)) {
			for(k = n/i, j = i*k; k >= i; k--, j -= i)
				SET(j);
			P[Pt++] = i;
		}
	}
}
#define MAXN 65536 
#define MAXE (1<<23) 
#define MAXV 524288
vector<int> g[MAXN];
void addEdge(int x, int y) {
    g[x].push_back(y);
}
int mx[MAXN], my[MAXN], used[MAXN], visited[MAXN];
int dfs(int now) {
    int i, x;
    for(i = 0; i < g[now].size(); i++) {
        x = g[now][i];
        if(!used[x]) {
            used[x] = 1;
            if(my[x] == -1 || dfs(my[x])) {
                mx[now] = x, my[x] = now;
                return 1;
            }
        }
    }
    return 0;
}
int greedy_matching(int n) {
    int c = 0;
    for (int x = 1; x <= n; ++x) {
        if (mx[x] == -1 && visited[x]%2 == 1) {
            for (int y, i = 0; i < g[x].size(); i++) {
            	y = g[x][i];
                if (my[y] == -1) {
                    mx[x] = y; my[y] = x;
                    c++;
                    break;
                }
            }
    	}
    }
    return c;
}
int A[MAXN], RE[MAXV], XY[MAXV];
int main() {
	sieve();
	for (int i = 2; i < MAXV; ++i){
        for (int j = 0; j < Pt && P[j] <= i && P[j] < 7200; ++j)
            if (i%P[j] == 0) {
                XY[i] = XY[i/P[j]]+1;
                break;
            }
        if (!XY[i]) XY[i] = 1;
    }
	int testcase, cases = 0;
	int n, x;
	scanf("%d", &testcase);
	while (testcase--) {	
		memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
   		scanf("%d", &n);
   		memset(RE, 0, sizeof(RE));
   		for (int i = 1; i <= n; i++) {
   			scanf("%d", &A[i]);
   			RE[A[i]] = i;
   			g[i].clear();
   		}
   		for (int i = 1; i <= n; i++) {
   			for (int j = 0; j < Pt && A[i] * P[j] <= 500000; j++) {
   				if (RE[A[i] * P[j]]) {
   					if (XY[A[i]]&1)
   						addEdge(i, RE[A[i] * P[j]]);
   					else
   						addEdge(RE[A[i] * P[j]], i);
   				}
   			}
   		}
   		int match = greedy_matching(n);
   		for (int i = 1; i <= n; i++) {
   			if (mx[i] == -1) {
   				memset(used, 0, sizeof(used));
   				if (dfs(i))
   					match++;
   			}
   		}
   		printf("Case %d: %d\n", ++cases, n - match);
   	}
    return 0;
}
/*
3
5
2 4 8 16 32
5
2 3 4 6 9
3
1 2 3

1000
3
7 35 105
*/

