#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#define oo 1000000000
using namespace std;
typedef struct {
    int to, v;
} Arc;
vector<Arc> myLink[20000];
void SPFA(int n, int st, int ed) {
    bool used[n];
    int dis[n];
    memset(used, 0, sizeof(used));
    for(int i = 0; i < n; i++)
        dis[i] = oo;
    queue<int> Q;
    Q.push(st);
    dis[st] = 0;
    int tv;
    while(!Q.empty()) {
        tv = Q.front();
        Q.pop();
        used[tv] = 0;
        for(vector<Arc>::iterator i = myLink[tv].begin(); i != myLink[tv].end(); i++) {
            if(dis[i->to] > dis[tv] + i->v) {
                dis[i->to] = dis[tv] + i->v;
                if(!used[i->to]) {
                    used[i->to] = true;
                    Q.push(i->to);
                }
            }
        }
    }
    if(dis[ed] == oo)
        puts("unreachable");
    else
        printf("%d\n", dis[ed]);
}
int main() {
    int N, Case = 0, i;
    int x, y, w, n, m, S, T;
    scanf("%d", &N);
    while(N--) {
        scanf("%d %d %d %d", &n, &m, &S, &T);
        for(i = 0; i < n; i++) {
            myLink[i].clear();
        }
        Arc tmp;
        while(m--) {
            scanf("%d %d %d", &x, &y, &tmp.v);
            tmp.to = y;
            myLink[x].push_back(tmp);
            tmp.to = x;
            myLink[y].push_back(tmp);
        }
        printf("Case #%d: ", ++Case);
        SPFA(n, S, T);
    }
    return 0;
}
