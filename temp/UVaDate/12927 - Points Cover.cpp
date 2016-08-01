#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
using namespace std;

const int MAXN = 65536;
struct Node {
    int y;
    int next;
} edge[1048576];
int e, head[MAXN];

void addEdge(int x, int y) {
    edge[e].y = y;
    edge[e].next = head[x], head[x] = e++;
}
int mx[MAXN], my[MAXN], used[MAXN];
stack<int> stk;
int dfs(int now) {
    int i, x;
    for (i = head[now]; i != -1; i = edge[i].next) {
        x = edge[i].y;
        if (!used[x]) {
            used[x] = 1;
            stk.push(x);
            if (my[x] == -1 || dfs(my[x])) {
                mx[now] = x, my[x] = now;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
	int testcase;
	int n;
	int X[MAXN], Y[MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		map<int, int> RX, RY; 
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &X[i], &Y[i]);
			RX[X[i]] = 0, RY[Y[i]] = 0;
		}
		
		int N = 0, M = 0;
		for (auto&x : RX)
			x.second = N++;
		for (auto&y : RY)
			y.second = M++;
		
		e = 0;
        memset(head, -1, sizeof(head));
		
		for (int i = 0; i < n; i++) {
			int u = RX[X[i]], v = RY[Y[i]];
			addEdge(u, v);
		}
		
		for (int i = 0; i <= N; i++)
			mx[i] = -1;
		for (int i = 0; i <= M; i++)
			my[i] = -1;
			
		int match = 0;
        for(int i = 0; i < N; i++) {
            if(mx[i] == -1) {
                if(dfs(i))
                    match++;
                while (!stk.empty())
                	used[stk.top()] = 0, stk.pop();
            }
        }
		printf("%d\n", match);
	}
	return 0;
}
/*
3
1
3 4
4
1 1
2 1
1 2
2 2
10
1 1
1 2
2 1
2 2
2 3
2 4
3 2
4 2
3 3
4 4
*/
