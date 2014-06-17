#include <stdio.h>
#include <vector>
#include <queue>
#define oo 0xfffffff
using namespace std;
struct arc {
    int to, w;
    arc(int x, int y): to(x), w(y) {}
};
vector<arc> g[51];
int dis[51][51], used[51][51];
void spfa(int st, int n, double& cut) {
    static int i, j;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            dis[i][j] = oo;
            used[i][j] = 0;
        }
    }
    queue<arc> Q;
    dis[st][0] = 0;
    Q.push(arc(st, 0));
    arc A(0,0);
    while(!Q.empty()) {
        A = Q.front(), Q.pop();
        used[A.to][A.w] = 0;
        for(vector<arc>::iterator it = g[A.to].begin();
            it != g[A.to].end(); it++) {
            if(dis[it->to][A.w+1] > dis[A.to][A.w] + it->w) {
                dis[it->to][A.w+1] = dis[A.to][A.w] + it->w;
                if(!used[it->to][A.w+1]) {
                    used[it->to][A.w+1] = 1;
                    Q.push(arc(it->to, A.w+1));
                }
            }
        }
    }
    for(i = 1; i <= n; i++)
        if(dis[st][i] != oo)
            cut = min(cut, (double)dis[st][i]/i);
}
int main() {
    scanf("%*d");
    int n, m, i, a, b, c;
    int cases = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++)
            g[i].clear();
        while(m--) {
            scanf("%d %d %d", &a, &b, &c);
            g[a].push_back(arc(b,c));
        }
        double ans = 0xfffffff;
        for(i = 1; i <= n; i++)
            spfa(i, n, ans);
        printf("Case #%d: ", ++cases);
        if(ans == 0xfffffff)
            puts("No cycle found.");
        else
            printf("%.2lf\n", ans);
    }
    return 0;
}
