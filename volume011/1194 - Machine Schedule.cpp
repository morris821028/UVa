#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Node {
    int y;
    int next;
} edge[10005];
int e, head[105];
void addEdge(int x, int y) {
    edge[e].y = y;
    edge[e].next = head[x], head[x] = e++;
}
int mx[105], my[105], used[105];
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
int main() {
	int N, M, K, u, v;
	while(scanf("%d %d %d", &N, &M, &K) == 3 && N) {
		e = 0;
    	memset(head, -1, sizeof(head));	
    	for(int i = 0; i < K; i++) {
    		scanf("%*d %d %d", &u, &v);
    		if(u > 0 && v > 0)
    			addEdge(u, v);
    	}
    	memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        int match = 0;
        for(int i = 0; i < N; i++) {
            if(mx[i] == -1) {
                memset(used, 0, sizeof(used));
                if(dfs(i))
                    match++;
            }
        }
        printf("%d\n", match);
	}
    return 0;
}
