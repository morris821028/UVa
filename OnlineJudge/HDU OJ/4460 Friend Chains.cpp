#include <stdio.h>
#include <map>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
vector<int> g[1000];
int dist[1000], used[1000];
int spfa(int st, int n) {
    static int i, tn;
    for(i = 0; i < n; i++)
        dist[i] = 0xffff, used[i] = 0;
    dist[st] = 0;
    queue<int> Q;
    Q.push(st);
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn] = 0;
        for(i = g[tn].size()-1; i >= 0; i--) {
            if(dist[g[tn][i]] > dist[tn]+1) {
                dist[g[tn][i]] = dist[tn]+1;
                if(used[g[tn][i]] == 0) {
                    Q.push(g[tn][i]);
                    used[g[tn][i]] = 1;
                }
            }
        }
    }
    int res = 0;
    for(i = 0; i < n; i++) {
        if(res < dist[i])
            res = dist[i];
    }
    return res;
}
int main() {
    char s[20], x[20], y[20];
    int n, m, i, tx, ty;
    while(scanf("%d", &n) == 1 && n) {
        map<string, int> r;
        for(i = 0; i < n; i++) {
            scanf("%s", s);
            r[s] = i;
            g[i].clear();
        }
        scanf("%d", &m);
        while(m--) {
            scanf("%s %s", x, y);
            tx = r[x], ty = r[y];
            g[tx].push_back(ty);
            g[ty].push_back(tx);
        }
        int ans = 0, tmp;
        for(i = 0; i < n; i++) {
            tmp = spfa(i, n);
            if(tmp > ans)
                ans = tmp;
            if(ans == 0xffff) {
                ans = -1;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
