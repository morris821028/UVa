#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
vector<int> g[700];
int dist[700], used[700], pre[700];
void spfa(int ed, int st) {
    int i, tn;
    for(i = 0; i < 700; i++)
        dist[i] = 0xffff, used[i] = 0;
    dist[st] = 0, pre[st] = st;
    queue<int> Q;
    Q.push(st);
    while(!Q.empty()) {
        tn = Q.front();
        used[tn] = 0;
        Q.pop();
        for(i = 0; i < g[tn].size(); i++) {
            if(dist[g[tn][i]] > dist[tn]+1) {
                dist[g[tn][i]] = dist[tn]+1;
                pre[g[tn][i]] = tn;
                if(used[g[tn][i]] == 0) {
                    used[g[tn][i]] = 1;
                    Q.push(g[tn][i]);
                }
            }
        }
    }
    if(dist[ed] == 0xffff)
        puts("No route");
    else {
        int idx = ed;
        while(dist[idx]) {
            printf("%c%c %c%c\n", idx/26+'A', idx%26+'A', pre[idx]/26+'A', pre[idx]%26+'A');
            idx = pre[idx];
        }
    }
}
int main() {
    int n;
    char x[30], y[30];
    int first = 0;
    while(scanf("%d", &n) == 1) {
        if(first)
            puts("");
        first = 1;
        int xx, yy, i;
        for(i = 0; i < 700; i++)
            g[i].clear();
        while(n--) {
            scanf("%s %s", x, y);
            xx = (x[0]-'A')*26 + x[1]-'A';
            yy = (y[0]-'A')*26 + y[1]-'A';
            g[xx].push_back(yy);
            g[yy].push_back(xx);
        }
        scanf("%s %s", x, y);
        xx = (x[0]-'A')*26 + x[1]-'A';
        yy = (y[0]-'A')*26 + y[1]-'A';
        spfa(xx, yy);
    }
    return 0;
}
