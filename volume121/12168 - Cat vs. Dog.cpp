#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <vector>
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
	int testcase, C, D, N;
	scanf("%d", &testcase);
	while(testcase--) {
		e = 0;
        memset(head, -1, sizeof(head));
        
        memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        
        scanf("%d %d %d", &C, &D, &N);
        char s1[512][16], s2[512][16];
        vector<int> L, R;
        for(int i = 0; i < N; i++) {
        	scanf("%s %s", s1[i], s2[i]);
        	if(s1[i][0] == 'C')
        		L.push_back(i);
        	else
        		R.push_back(i);
        }
        for(int i = 0; i < L.size(); i++) {
        	for(int j = 0; j < R.size(); j++) {
        		int p = L[i], q = R[j];
        		if(!strcmp(s1[p], s2[q]) || !strcmp(s2[p], s1[q]))
        			addEdge(i, j);
        	}
        }
        int match = 0;
        for(int i = 0; i < L.size(); i++) {
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
