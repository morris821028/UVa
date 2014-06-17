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
double dis[51];
int used[51], inq[51];
int negCycle(int n, double m) {
    static int i, tn;
    queue<int> Q;
    for(i = 1; i <= n; i++) {
        dis[i] = 0, used[i] = 1, inq[i] = 0;
        Q.push(i);
    }
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        used[tn] = 0;
        for(vector<arc>::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            if(dis[it->to] > dis[tn] + it->w - m) {
                dis[it->to] = dis[tn] + it->w - m;
                if(!used[it->to]) {
                    used[it->to] = 1;
                    Q.push(it->to);
                    if(++inq[it->to] > n)
                        return 1;
                }
            }
        }
    }
    return 0;
}
int main() {
    scanf("%*d");
    int n, m, i, a, b, c;
    int cases = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++)
            g[i].clear();
        double l = 0, r = 0, mid;
        while(m--) {
            scanf("%d %d %d", &a, &b, &c);
            g[a].push_back(arc(b,c));
            if(c > r)   r = c;
        }
        r += 10;
        printf("Case #%d: ", ++cases);
        if(!negCycle(n, r)) {
            puts("No cycle found.");
            continue;
        }
        while(r - l > 1e-4) {
            mid = (l+r)/2;
            if(negCycle(n, mid))
                r = mid;
            else
                l = mid;
        }
        printf("%.2lf\n", r);
    }
    return 0;
}
