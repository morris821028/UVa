#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
struct Arc {
    int to, v;
};
vector<Arc> nd[301];
int n, m, k;
int spfa() {
    int dis[301][1001] = {}, noans;
    memset(dis, 63, sizeof(dis));
    noans = dis[0][0];
    queue<Arc> Q;
    dis[1][0] = 0;
    Arc tmp, tn;
    tmp.to = 1, tmp.v = 0;
    Q.push(tmp);
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        for(vector<Arc>::iterator i = nd[tn.to].begin(); i != nd[tn.to].end(); i++) {
            int ll = tn.v + i->v;
            ll %= k;
            if(dis[i->to][ll] != 0) {
                dis[i->to][ll] = 0;
                tmp.to = i->to, tmp.v = ll;
                Q.push(tmp);
            }
        }
    }
    int ans = noans, i;
    for(i = 0; i < k; i++)
        if(dis[n][i] == 0) {
            ans = i;
            break;
        }
    if(ans == noans)
        puts("NO_WAY!");
    else
    printf("%d\n", ans);
}
/*
*/
int main() {
    int i;
    while(scanf("%d %d %d", &n, &m, &k) == 3) {
        for(i = 1; i <= n; i++)
            nd[i].clear();
        Arc tmp;
        int x, y, v;
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &v);
            tmp.to = y, tmp.v = v;
            nd[x].push_back(tmp);
        }
        spfa();
    }
    return 0;
}
