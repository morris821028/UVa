#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
struct E {
    int x, y, d;
    bool operator<(const E &a) const {
        return x < a.x;
    }
} D[10000];
#define maxN 4096
vector<int> g[maxN];
int vfind[maxN], findIdx;
int stk[maxN], stkIdx;
int in_stk[maxN], visited[maxN];
int scc_cnt;
int contract[maxN];
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd]; // back edge
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(!visited[*it])
            mn = min(mn, scc(*it));
        if(in_stk[*it])
            mn = min(mn, vfind[*it]);
    }
    if(mn == vfind[nd]) {
        do {
            in_stk[stk[stkIdx]] = 0;
            contract[stk[stkIdx]] = nd;
        } while(stk[stkIdx--] != nd);
        scc_cnt++;
    }
    return mn;
}
int main() {
    int t, n, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d %d %d", &D[i].x, &D[i].y, &D[i].d);
        sort(D, D+n);
        int indeg[2005] = {}, x, y, d;
        for(i = 0; i < n; i++) {
            g[i].clear();
            d = D[i].d;
            x = D[i].x;
            y = D[i].y;
            for(j = i+1; j < n; j++) {
                if(D[j].x - x > d/2.0)
                    break;
                if(y-d/2.0 <= D[j].y && D[j].y <= y+d/2.0)
                    g[i].push_back(j);
            }
            for(j = i-1; j >= 0; j--) {
                if(x - D[j].x > d/2.0)
                    break;
                if(y-d/2.0 <= D[j].y && D[j].y <= y+d/2.0)
                    g[i].push_back(j);
            }
        }
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        scc_cnt = 0;
        for(i = 0; i < n; i++) {
            if(!visited[i]) {
                findIdx = stkIdx = 0;
                scc(i);
            }
        }
        for(i = 0; i < n; i++) {//become DAG
            x = contract[i];
            //printf("contract %d\n", x);
            for(vector<int>::iterator it = g[i].begin();
                it != g[i].end(); it++) {
                y = contract[*it];
                if(x != y)
                    indeg[y]++;
            }
        }
        int ret = 0;
        for(i = 0; i < n; i++)
            if(indeg[i] == 0 && i == contract[i])
                ret++;
        printf("%d\n", ret);
    }
    return 0;
}
