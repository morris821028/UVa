#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1024;
struct Node {
    int y;
    int next;
} edge[65536];
int e, head[MAXN];

void addEdge(int x, int y) {
    edge[e].y = y;
    edge[e].next = head[x], head[x] = e++;
}
int mx[MAXN], my[MAXN], used[MAXN];
int dfs(int now) {
    int i, x;
    for (i = head[now]; i != -1; i = edge[i].next) {
        x = edge[i].y;
        if (!used[x]) {
            used[x] = 1;
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
	int n, m;
	int Nx[128], Ny[128], Mx[128], My[128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d %d", &Nx[i], &Ny[i]);
		for (int i = 0; i < m; i++)
			scanf("%d %d", &Mx[i], &My[i]);
		
		e = 0;
        memset(head, -1, sizeof(head));
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (abs(Nx[i]-Mx[j]) + abs(Ny[i]-My[j]) <= 5)
					addEdge(i, j);
			}
		}
		
		memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
		int match = 0;
        for(int i = 0; i < n; i++) {
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
