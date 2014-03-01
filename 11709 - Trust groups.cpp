#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#define maxN 1005
using namespace std;
vector<int> g[maxN];
int vfind[maxN], findIdx;
int stk[maxN], stkIdx;
int in_stk[maxN], visited[maxN];
int scc_cnt;
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
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
        } while(stk[stkIdx--] != nd);
        scc_cnt++;
    }
    return mn;
}
int main() {
    int n, m, x, y, i;
    char name[50], a[50], b[50];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        map<string, int> mapped;
        getchar();
        for(i = 0; i < n; i++) {
            gets(name);
            mapped[name] = i;
            g[i].clear();
            visited[i] = in_stk[i] = 0;
        }
        for(i = 0; i < m; i++) {
            gets(a);
            gets(b);
            x = mapped[a];
            y = mapped[b];
            g[x].push_back(y);
        }
        scc_cnt = 0;
        for(i = 0; i < n; i++) {
            if(!visited[i]) {
                findIdx = stkIdx = 0;
                scc(i);
            }
        }
        printf("%d\n", scc_cnt);
    }
    return 0;
}
