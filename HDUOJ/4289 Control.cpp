#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int C[405][405], F[405][405];
vector<int> g[405];
int ans;
int maxflow(int st, int ed, int n) {
    int v[405], pre[405];
    int maxflow = 0, i, tn, tc;
    bool used[405];
    memcpy(F, C, sizeof(F));
    while(true) {
        for(i = 0; i <= n; i++)
            v[i] = 0, used[i] = 0;
        v[st] = 2147483647;
        queue<int> Q;
        Q.push(st);
        pre[st] = st;
        while(!Q.empty()) {
            tn = Q.front();
            Q.pop();
            used[tn] = false;
            for(vector<int>::iterator i = g[tn].begin(); i != g[tn].end(); i++) {
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
            if(v[ed])
                break;
        }
        if(v[ed] == 0)
            break;
        maxflow += v[ed];
        if(maxflow >= ans)
            return maxflow;
        for(i = ed; i != st; i = pre[i]) {
            F[pre[i]][i] -= v[ed];
            F[i][pre[i]] += v[ed];
        }
    }
    return maxflow;
}
int main() {
    int n, m, S, D;
    int A[205], i, x, y;
    while(scanf("%d %d", &n, &m) == 2) {
        scanf("%d %d", &S, &D);
        for(i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        for(i = 1; i <= 2*n; i++)
            g[i].clear();
        memset(C, 0, sizeof(C));
        while(m--) {
            scanf("%d %d", &x, &y);
            C[2*x][2*y-1] = 2147483647;
            C[2*y][2*x-1] = 2147483647;
            g[2*x-1].push_back(2*y);
            g[2*y-1].push_back(2*x);
            g[2*y].push_back(2*x-1);
            g[2*x].push_back(2*y-1);
        }
        for(i = 1; i <= n; i++) {
            C[2*i-1][2*i] = A[i];
            C[2*i][2*i-1] = A[i];
            g[2*i-1].push_back(2*i);
            g[2*i].push_back(2*i-1);
        }
        ans = min(A[S], A[D]);
        ans = maxflow(2*S-1, 2*D, 2*n);
        printf("%d\n", ans);
    }
    return 0;
}
