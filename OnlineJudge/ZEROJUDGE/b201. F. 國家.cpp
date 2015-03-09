#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#define maxN 100010
using namespace std;
vector<int> g[maxN];
int stk[maxN], stkIdx;
int visited[maxN], in_stk[maxN];
int vfind[maxN], findIdx;
int lead[maxN];
int group[maxN], gIdx;
int scc(int nd) {
    visited[nd] = in_stk[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(!visited[*it]) {
            mn = min(mn, scc(*it));
        }
        if(in_stk[*it]) {
            mn = min(mn, vfind[*it]);
        }
    }
    if(mn == vfind[nd]) {
        int cnt = 0;
        do {
            cnt++;
            lead[stk[stkIdx]] = nd;
            in_stk[stk[stkIdx]] = 0;
        } while(stk[stkIdx--] != nd);
        group[++gIdx] = cnt;
    }
    return mn;
}
int main() {
    int n, m, x, y;
    int i;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++) {
            g[i].clear();
            vfind[i] = visited[i] = in_stk[i] = 0;
            lead[i] = i;
        }
        while(m--) {
            scanf("%d %d", &x, &y);
            g[x].push_back(y);
        }
        gIdx = -1;
        for(i = 1; i <= n; i++) {
            if(!visited[i]) {
                findIdx = 0, stkIdx = -1;
                scc(i);
            }
        }
        sort(group, group+gIdx+1);
        printf("%d", group[0]);
        for(i = 1; i <= gIdx; i++)
            printf(" %d", group[i]);
        puts("");
    }
    return 0;
}
