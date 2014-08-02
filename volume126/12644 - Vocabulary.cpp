#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Node {
    int y;
    int next;
} edge[100005];
int e, head[512];
void addEdge(int x, int y) {
    edge[e].y = y;
    edge[e].next = head[x], head[x] = e++;
}
int mx[512], my[512], used[512];
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
	int V, C;
	char s[512];
	while(scanf("%d %d", &V, &C) == 2) {
		e = 0;
    	memset(head, -1, sizeof(head));
    	
		int Vcnt[512][26] = {}, Ccnt[512][26] = {};
		for(int i = 0; i < V; i++) {
			scanf("%s", s);
			for(int j = 0; s[j]; j++)
				Vcnt[i][s[j] - 'a']++;
		}
		for(int i = 0; i < C; i++) {
			scanf("%s", s);
			for(int j = 0; s[j]; j++)
				Ccnt[i][s[j] - 'a']++;
		}
		for(int i = 0; i < V; i++) {
			for(int j = 0; j < C; j++) {
				int f = 1;
				for(int k = 0; k < 26; k++)
					f &= Vcnt[i][k] >= Ccnt[j][k];
				if(f)
					addEdge(i, j);
			}
		}
			
    	memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        int match = 0;
        for(int i = 0; i < V; i++) {
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
/*
1 1
icpc
pic
4 3
sequoia
march
may
tree
ae
aeiou
acm
*/
