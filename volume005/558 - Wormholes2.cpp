#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
typedef struct {
    int to, v;
} Arc;
typedef vector<Arc>::iterator it;
vector<Arc> link[1000];
bool used[1000];
int dis[1000], inQu[1000];
int checkNegCycle(int n) {
    int i;
    queue<int> Q;
    memset(used, 0, n);
    memset(inQu, 0, 4*n);
    memset(dis, 0, 4*n);
    for(i = 0; i < n; i++) {
        Q.push(i), used[i] = 1;
    }
    int tv;
    while(!Q.empty()) {
        tv = Q.front();
        Q.pop();
        used[tv] = false;
        for(it i = link[tv].begin(); i != link[tv].end(); i++) {
            if(dis[i->to] > dis[tv] + i->v) {
                dis[i->to] = dis[tv] + i->v;
                if(!used[i->to]) {
                    used[i->to] = true;
                    Q.push(i->to);
                    inQu[i->to]++;
                }
                if(inQu[i->to] >= n)
                    return 1;
            }
        }
    }
    return 0;
}
int main() {
    int t, n, m, i;
    int x, y, v;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            link[i].clear();
        }
        Arc arc;
        while(m--) {
            scanf("%d %d %d", &x, &y, &v);
            arc.to = y, arc.v = v;
            link[x].push_back(arc);
        }
        int find = checkNegCycle(n);
        if(find == 1)
            puts("possible");
        else
            puts("not possible");
    }
    return 0;
}
