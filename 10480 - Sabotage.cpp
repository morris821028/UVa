#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
bool diff[100];
int C[100][100], F[100][100], cost[100][100];
vector<int> map[100];
int maxFlow(int st, int ed, int n) {
    int v[100], pre[100];
    int maxflow = 0, i, tn, tc;
    bool used[100];
    memcpy(F, C, sizeof(F));
    while(true) {
        memset(v, 0, sizeof(v));
        memset(used, 0, sizeof(used));
        v[st] = 0xfffffff;
        queue<int> Q;
        Q.push(st);
        pre[st] = st;
        while(!Q.empty()) {
            tn = Q.front();
            Q.pop();
            used[tn] = false;
            for(vector<int>::iterator i = map[tn].begin(); i != map[tn].end(); i++) {
                tc = v[tn] < F[tn][*i] ? v[tn] : F[tn][*i];
                if(tc <= v[ed])
                    continue;
                if(tc > v[*i]) {
                    v[*i] = tc, pre[*i] = tn;
                    if(used[*i] == false) {
                        Q.push(*i);
                        used[*i] = true;
                    }
                }
            }
        }
        if(v[ed] == 0)
            break;
        maxflow += v[ed];
        for(i = ed; i != st; i = pre[i]) {
            F[pre[i]][i] -= v[ed];
            F[i][pre[i]] += v[ed];
        }
    }
    return maxflow;
}
int main() {
    int n, m, x, y, c;
    int i, j;

    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        for(i = 0; i <= n; i++)
            map[i].clear();
        memset(C, 0, sizeof(C));
        while(m--) {
            scanf("%d %d %d", &x, &y, &c);
            C[x][y] += 2;
            C[y][x] += 2;
            cost[x][y] = c;
            cost[y][x] = c;
            map[x].push_back(y);
            map[y].push_back(x);
        }
        minCut(1, 2, n);
        puts("");
    }
    return 0;
}
