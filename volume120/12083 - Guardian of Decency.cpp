#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Node {
    int y;
    int next;
} edge[250005];
int e, head[505];
void addEdge(int x, int y) {
    edge[e].y = y;
    edge[e].next = head[x], head[x] = e++;
}
int mx[505], my[505], used[505];
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
	int testcase, N;
	int h[512];
	char sex[512][128], music[512][128], sport[512][128];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &N);
		for(int i = 0; i < N; i++)
			scanf("%d %s %s %s", &h[i], sex[i], music[i], sport[i]);
		e = 0;
        memset(head, -1, sizeof(head));
        for(int i = 0; i < N; i++) {
        	if(!strcmp(sex[i], "M"))
        	for(int j = 0; j < N; j++) {
        		if(strcmp(sex[i], sex[j]) && abs(h[i] - h[j]) <= 40 && 
					!strcmp(music[i], music[j]) && strcmp(sport[i], sport[j])) 
					addEdge(i, j);
        	}
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
        printf("%d\n", N - match);
	}
	return 0;
}
/*
2
4
35 M classicism programming
0 M baroque skiing
43 M baroque chess
30 F baroque soccer
8
27 M romance programming
194 F baroque programming
67 M baroque ping-pong
51 M classicism programming
80 M classicism Paintball
35 M baroque ping-pong
39 F romance ping-pong
110 M romance Paintball
*/
