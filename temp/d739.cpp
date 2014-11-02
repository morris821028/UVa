#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 65536 
#define MAXE (1<<21) 
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
int mx[MAXN], my[MAXN], used[MAXN];
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
        if (mx[x] == -1) {
            for (int y = 0, i = head[x]; i != -1; i = edge[i].next) {
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
int main() {
	int testcase, cases = 0;
	int N, M, x, y;
	while (scanf("%d %d", &N, &M) == 2 && N) {
		e = 0;
		memset(head, -1, sizeof(head));
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			addEdge(x, y);
		}
		memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        
        int match = greedy_matching(N);
        for(int i = 1; i <= N; i++) {
            if(mx[i] == -1) {
                memset(used, 0, sizeof(used));
                if(dfs(i))
                    match++;
            }
        }
		printf("%d\n", N - match);
	}
	return 0;
} 
/*
2
1 36
20
2 40
8 20
*/ 
 
