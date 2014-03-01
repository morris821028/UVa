#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
vector<pair<int, int> > g[205];
int dist[205], n;
void spfa(int st) {
    int inq[205] = {}, tn;
    int cnt[205] = {}, neg[205] = {};
    queue<int> Q;
    dist[st] = 0;
    Q.push(st);
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        inq[tn] = 0;
        for(vector<pair<int, int> >::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            if(dist[it->first] > dist[tn] + it->second) {
                dist[it->first] = dist[tn] + it->second;
                if(inq[it->first] == 0) {
                    if(++cnt[it->first] >= n+1) {
                        queue<int> nq;
                        nq.push(it->first);
                        neg[it->first] = 1;
                        while(!nq.empty()) {
                            int tn = nq.front();
                            nq.pop();
                            dist[tn] = -0xfffffff;
                            for(vector<pair<int, int> >::iterator it = g[tn].begin();
                                it != g[tn].end(); it++) {
                                if(neg[it->first] == 0) {
                                    neg[it->first] = 1;
                                    nq.push(it->first);
                                }
                            }
                        }
                    }
                    if(neg[it->first] == 0) {
                        Q.push(it->first);
                        inq[it->first] = 1;
                    }
                }
            }
        }
    }
}
int main() {
    int m, C[205];
    int i, j, x, y;
    int cases = 0;
    while(scanf("%d", &n) == 1) {
        for(i = 1; i <= n; i++) {
            scanf("%d", &C[i]);
            dist[i] = 0xfffffff;
            g[i].clear();
        }
        scanf("%d", &m);
        while(m--) {
            scanf("%d %d", &x, &y);
            g[x].push_back(make_pair(y, (C[y]-C[x])*(C[y]-C[x])*(C[y]-C[x])));
        }
        scanf("%d", &m);
        spfa(1);
        printf("Set #%d\n", ++cases);
        while(m--) {
            scanf("%d", &x);
            if(x <= 0 || x > n || dist[x] < 3 || dist[x] == 0xfffffff)
                puts("?");
            else
                printf("%d\n", dist[x]);
        }
    }
    return 0;
}
/*
5 6 7 8 9 10
6
1 2
2 3
3 4
1 5
5 4
4 5
2
4
5
*/
