#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
struct edg {
    int to, w;
};
vector<edg> g[1000005];
int used[1000005], son[1000005], p[1000005], n;
int main() {
    int i, x, y, w, tn;
    scanf("%d", &n);
    for(i = 1; i < n; i++) {
        scanf("%d %d %d", &x, &y, &w);
        edg tmp;
        tmp.to = y, tmp.w = w;
        g[x].push_back(tmp);
        tmp.to = x;
        g[y].push_back(tmp);
    }
    queue<int> Q;
    stack<int> S;
    Q.push(1), used[1] = 1;
    S.push(1);
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        son[tn] = 1;
        for(vector<edg>::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            if(!used[it->to]) {
                used[it->to] = 1;
                Q.push(it->to);
                S.push(it->to);
                p[it->to] = tn;
            }
        }
    }
    long long ans = 0, tmp;
    while(!S.empty()) {
        tn = S.top(), S.pop();
        for(vector<edg>::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            if(it->to != p[tn]) {
                tmp = (son[it->to]-(n-son[it->to]));
                if(tmp < 0) tmp *= -1;
                tmp *= it->w;
                ans += tmp;
            }
        }
        son[p[tn]] += son[tn];
    }
    printf("%lld\n", ans);
    return 0;
}
