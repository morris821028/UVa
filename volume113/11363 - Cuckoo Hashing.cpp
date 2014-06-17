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
int e, head[10005];
void addEdge(int x, int y) {
    edge[e].y = y;
    edge[e].next = head[x], head[x] = e++;
}
int mx[10005], my[10005], used[10005];
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
    int testcase, n, m;
    int i, j, x, y;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        e = 0;
        memset(head, -1, sizeof(head));
        for(i = 0; i < n; i++) {
        	scanf("%d %d", &x, &y);
        	addEdge(i, x);
        	addEdge(i, y);
        }
        memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        int match = 0;
        for(i = 0; i < n; i++) {
            if(mx[i] == -1) {
                memset(used, 0, sizeof(used));
                if(dfs(i))
                    match++;
                else
                    break;// cut condition.
            }
        }
        puts(match == n ? "successful hashing" : "rehash necessary");
    }
    return 0;
} 
