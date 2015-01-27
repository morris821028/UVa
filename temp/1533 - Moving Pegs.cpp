#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <set>
#include <assert.h>
#include <iostream>
using namespace std;
#define MAXN 15
#define MAXSTATE (1<<16)
const int table[5][5] = {
    { 1, -1, -1, -1, -1},
    { 2,  3, -1, -1, -1},
    { 4,  5,  6, -1, -1},
    { 7,  8,  9, 10, -1},
    {11, 12, 13, 14, 15}
};
const int dx[] = {0,  0, -1, 1, -1, 1};
const int dy[] = {-1, 1, -1, 1, 0,  0};
struct state {
    int mask;
    int posA, posB, dist;
    int searchEnd;
    state *prev;
} states[MAXSTATE];
struct edge {
    state *to;
    int posA, posB;
    edge(state *a = NULL, int b = 0, int c = 0):
    to(a), posA(b), posB(c) {}
    bool operator<(const edge &x) const {
        return make_pair(posA, posB) < make_pair(x.posA, x.posB);
    }
};
int stateSize = 0;
state* mapR[MAXSTATE];
void getPos(int val, int &x, int &y) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == val) {
                x = i, y = j;
                return ;
            }
        }
    }
}

void bfs(int st, int finalState) {
    queue<state*> Q;
    vector<state*> dp;
    vector<edge> g[1<<MAXN];
    int used[1<<MAXN] = {}, x, y;
    state *u, *v;
    stateSize = 0;
    u = &states[stateSize++];
    u->mask = st, u->prev = NULL, u->dist = 0, u->searchEnd = 0;
    used[st] = 1, mapR[st] = u;
    Q.push(u);
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        dp.push_back(u);
        if (u->mask == finalState) {
            printf("%d\n", u->dist);
            u->searchEnd = 1;
            for (int i = (int)dp.size() - 1; i >= 0; i--) {
                int mask = dp[i]->mask, d = dp[i]->dist;
                for (int j = 0; j < g[mask].size(); j++) {
                    if (d + 1 == g[mask][j].to->dist)
                        dp[i]->searchEnd |= g[mask][j].to->searchEnd;
                }
            }
            u = dp[0];
            
            vector< pair<int, int> > step;
            while (u != dp[dp.size() - 1]) {
                int mask = u->mask, d = u->dist;
                for (int j = 0; j < g[mask].size(); j++) {
                    if (d + 1 == g[mask][j].to->dist && g[mask][j].to->searchEnd) {
                        u = g[mask][j].to;
                        step.push_back(make_pair(g[mask][j].posA, g[mask][j].posB));
                        break;
                    }
                }
            }
            for (int i = 0; i < step.size(); i++) {
                printf("%d %d%c", step[i].first, step[i].second, i == step.size()-1 ? '\n' : ' ');
            }
            return;
        }
        for (int i = 0; i < MAXN; i++) {
            if (((u->mask)>>i)&1)
                continue; // find i-hole
            for (int j = 0; j < 6; j++) {
                getPos(i + 1, x, y);
                x += dx[j], y += dy[j];
                int cnt = 0, pass = 0;
                while (0 <= x && x < 5 && 0 <= y && y < 5) {
                    int p = table[x][y];
                    x += dx[j], y += dy[j];
                    if (p == -1 || ((u->mask)>>(p-1)&1) == 0)
                        break;
                    cnt++;
                    pass |= 1<<(p-1);
                    if (cnt > 1) { // jump one or more
                        int nmask = u->mask;
                        nmask ^= pass, nmask ^= 1<<i;
                        if (used[nmask] == 0) {
                            used[nmask] = 1;
                            v = &states[stateSize++];
                            v->mask = nmask, v->prev = u;
                            v->dist = u->dist + 1, v->posA = p, v->posB = i+1;
                            v->searchEnd = 0;
                            mapR[nmask] = v;
                            Q.push(v);
                        }
                        g[u->mask].push_back(edge(mapR[nmask], p, i+1));
                    }
                }
            }
            sort(g[u->mask].begin(), g[u->mask].end());
        }
    }
    puts("IMPOSSIBLE");
}
int main() {
    int testcase, e;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &e);
        int state = (1<<MAXN) - 1;
        state ^= 1<<(e-1);
        bfs(state, 1<<(e-1));
    }
    return 0;
}
/*
 1
 5
*/