#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
double map[21][21];
int ans[40], alen;
struct Arc {
    int to, step;
};
int spfa(int st, int n) {
    double dis[21][21];
    int pre[21][21], used[21][21];
    memset(dis, 0, sizeof(dis));
    memset(used, 0, sizeof(used));
    int i, j;
    Arc tn, tmp;
    queue<Arc> Q;
    tn.to = st, tn.step = 0;
    Q.push(tn);
    dis[st][0] = 1;
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn.to][tn.step] = 0;
        if(tn.step > n || tn.step >= alen)
            continue;
        for(i = 1; i <= n; i++) {
            if(dis[tn.to][tn.step]*map[tn.to][i] > dis[i][tn.step+1]) {
                dis[i][tn.step+1] = dis[tn.to][tn.step]*map[tn.to][i];
                tmp.to = i, tmp.step = tn.step+1;
                pre[tmp.to][tmp.step] = tn.to;
                if(used[tmp.to][tmp.step] == 0) {
                    used[tmp.to][tmp.step] = 1;
                    Q.push(tmp);
                }
            }
        }
    }
    for(i = 1; i <= n; i++) {
        if(dis[st][i] > 1.01) {
            if(i < alen) {
                alen = i;
                j = st;
                while(i >= 0) {
                    ans[i] = j;
                    j = pre[j][i];
                    i--;
                }
            }
            return 0;
        }
    }
}
int main() {
    int n, i, j;
    while(scanf("%d", &n) == 1) {
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                if(i == j)
                    continue;
                scanf("%lf", &map[i][j]);
            }
            map[i][i] = 1;
        }
        alen = 0xffff;
        for(i = 1; i <= n; i++) {
            spfa(i, n);
        }
        if(alen != 0xffff) {
            for(i = 0; i <= alen; i++) {
                if(i)
                    putchar(' ');
                printf("%d", ans[i]);
            }
            puts("");
        } else {
            puts("no arbitrage sequence exists");
        }
    }
    return 0;
}
