#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <set>
#include <assert.h>
#include <iostream>
using namespace std;
#define MAXN 15
#define MAXSTATE (1<<20)

struct state {
    int mask, x;
    int posA, posB, dist;
    state *prev;
} states[MAXSTATE];
int stateSize = 0;
vector<int> g[MAXN + 10];
int used[(1<<MAXN)*MAXN], cases = 0;
void bfs(int mask, int st, int ed, int n) {
    ++cases;
    queue<state*> Q;
    state *u, *v;
    int x, y;
    stateSize = 0;
    u = &states[stateSize++];
    u->mask = mask, u->x = st, u->prev = NULL;
    used[(u->x)*(1<<MAXN) + u->mask] = cases;
    Q.push(u);
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        if (u->x == ed) {
            printf("%d\n", u->dist);
            vector< pair<int, int> > step;
            while (u->prev) {
                step.push_back(make_pair(u->posA + 1, u->posB + 1));
                u = u->prev;
            }
            for (int i = (int)step.size() - 1; i >= 0; i--) {
                printf("%d %d\n", step[i].first, step[i].second);
            }
            return;
        }
        for (int i = 0; i < n; i++) {
            if (((u->mask)>>i)&1) {
                x = i;
                for (int j = 0; j < g[i].size(); j++) {
                    y = g[i][j];
                    if (((u->mask)>>y)&1)
                        continue;
                    if (y == u->x)
                        continue;
                    int nmask = u->mask;
                    nmask ^= 1<<x;
                    nmask ^= 1<<y;
                    if (used[(u->x)*(1<<MAXN) + nmask] != cases) {
                        used[(u->x)*(1<<MAXN) + nmask] = cases;
                        v = &states[stateSize++];
                        v->mask = nmask, v->x = u->x, v->prev = u;
                        v->dist = u->dist + 1, v->posA = x, v->posB = y;
                        Q.push(v);
                    }
                }
            }
        }
        
        for (int i = 0; i < g[u->x].size(); i++) {
            y = g[u->x][i];
            if (((u->mask)>>y)&1)
                continue;
            int nmask = u->mask;
            if (used[(y)*(1<<MAXN) + nmask] != cases) {
                used[(y)*(1<<MAXN) + nmask] = cases;
                v = &states[stateSize++];
                v->mask = nmask, v->x = y, v->prev = u;
                v->dist = u->dist + 1, v->posA = u->x, v->posB = y;
                Q.push(v);
            }
        }
    }
    puts("-1");
}
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        int n, m, s, t, stone = 0, x, y;
        scanf("%d %d %d %d", &n, &m, &s, &t);
        for (int i = 0; i < m; i++) {
            scanf("%d", &x);
            x--, stone |= 1<<x;
        }
        for (int i = 0; i < n; i++)
            g[i].clear();
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &x, &y);
            x--, y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        printf("Case %d: ", ++cases);
        bfs(stone, s-1, t-1, n);
        puts("");
    }
    return 0;
}
/*
 3
 4 1 1 3
 2
 1 2
 2 3
 2 4
 6 2 1 4
 2 3
 1 2
 2 3
 3 4
 2 5
 2 6
 8 3 1 5
 2 3 4
 1 2
 2 3
 3 4
 4 5
 1 6
 1 7
 2 8
*/