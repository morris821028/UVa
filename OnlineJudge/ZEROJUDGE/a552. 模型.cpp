#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
struct info {
    int nd, deg;
    info(int a, int b) : nd(a), deg(b) {}
};
struct cmp {
    bool operator() (info a, info b) {
        if(a.deg != b.deg)
            return a.deg >= b.deg;
        return a.nd >= b.nd;
    }
};
int main() {
    int n, m, i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        vector<int> g[n];
        priority_queue<info, vector<info>, cmp> hp;
        int deg[100] = {}, used[100] = {};
        while(m--) {
            scanf("%d %d", &i, &j);
            g[i].push_back(j);
            deg[j]++;
        }
        for(i = 0; i < n; i++) {
            info e(i, deg[i]);
            hp.push(e);
        }
        while(!hp.empty()) {
            info t = hp.top();
            hp.pop();
            if(used[t.nd])  continue;
            printf("%d ", t.nd);
            used[t.nd] = 1;
            for(i = 0; i < g[t.nd].size(); i++) {
                if(!used[g[t.nd][i]]) {
                    deg[g[t.nd][i]]--;
                    info e(g[t.nd][i], deg[g[t.nd][i]]);
                    hp.push(e);
                }
            }
        }
        puts("");
    }
    return 0;
}
