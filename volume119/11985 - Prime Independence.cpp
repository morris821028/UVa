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
struct Node {
    int y;
    int next;
} edge[MAXE];
int e, head[MAXN];
void addEdge(int x, int y) {
    edge[e].y = y;
    edge[e].next = head[x], head[x] = e++;
}
int mx[MAXN], my[MAXN], used[MAXN], visited[MAXN];
int dfs(int now) {
    int i, x;
    for(i = head[now]; i != -1; i = edge[i].next) {
        x = edge[i].y;
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
            for (int y, i = head[x]; i != -1; i = edge[i].next) {
            	y = edge[i].y;
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
int A[MAXN], RE[MAXV];
int main() {
	sieve();
	int testcase, cases = 0;
	int n, x;
	scanf("%d", &testcase);
	while (testcase--) {
		e = 0;
		memset(head, -1, sizeof(head));		
		memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
   		scanf("%d", &n);
   		memset(RE, 0, sizeof(RE));
   		for (int i = 1; i <= n; i++) {
   			scanf("%d", &A[i]);
   			RE[A[i]] = i;
   		}
   		for (int i = 1; i <= n; i++) {
   			for (int j = 0; j < Pt && A[i] * P[j] <= 500000; j++) {
   				if (RE[A[i] * P[j]]) {
   					addEdge(i, RE[A[i] * P[j]]);
   					addEdge(RE[A[i] * P[j]], i);
   				}
   			}
   		}
   		memset(visited, 0, sizeof(visited));
   		int ret = 0;
   		for (int i = 1; i <= n; i++) {
   			if (visited[i] == 0) {
   				queue<int> Q;
   				Q.push(i), visited[i] = 1;
   				int odd = 0, even = 0;
   				while (!Q.empty()) {
   					x = Q.front(), Q.pop();
   					if (visited[x]&1)
   						odd++;
   					else
   						even++;
   					for (int i = head[x]; i != -1; i = edge[i].next) {
   						if (visited[edge[i].y] == 0) {
   							visited[edge[i].y] = visited[x] + 1;
   							Q.push(edge[i].y);
   						}
   					}
   				}
   				ret += max(odd, even);
   			}
   		}
   		printf("Case %d: %d\n", ++cases, ret);
//   		int match = greedy_matching(n);
//   		for (int i = 1; i <= n; i++) {
//   			if (mx[i] == -1 && visited[i]%2 == 1) {
//   				memset(used, 0, sizeof(used));
//   				if (dfs(i))
//   					match++;
//   			}
//   		}
//   		printf("Case %d: %d\n", ++cases, n - match);
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

