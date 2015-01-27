#include <stdio.h>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 32
int N, M, K;
char cg[MAXN][MAXN];
vector<int> g[MAXN * MAXN];
#define MAXSTATE 8000000
struct state {
    int c[3];
    int dist;
    bool operator<(const state &a) const {
        for (int i = 0; i < K; i++)
            if (c[i] != a.c[i])
                return c[i] < a.c[i];
        return false;
    }
    bool operator==(const state &a) const {
        int ok = 1;
        for (int i = 0; i < K; i++)
            ok &= c[i] == a.c[i];
        return ok == 1;
    }
    unsigned int index() {
        unsigned int value = 0;
        for (int i = 0; i < K; i++)
            value = value * 200 + c[i];
        return value;
    }
};
int usedA[MAXSTATE], usedB[MAXSTATE], dist[MAXSTATE];
int cases = 0, findflag = 0;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
queue<state> QA, QB;
int isValidPos(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < M && cg[x][y] == ' ';
}
int inRule(state u, state o) {
    for (int i = 0; i < K; i++) {
        for (int j = i+1; j < K; j++) {
            if (u.c[i] == u.c[j])
                return 0;
            if (u.c[i] == o.c[j] && u.c[j] == o.c[i])
                return 0;
        }
    }
    return 1;
}
void dfs(state u, state o, int idx, int dir) {
    if (findflag)   return;
    if (idx == K) {
        if (inRule(u, o)) {
            if (dir == 0) {
                if (usedB[u.index()] == cases) {
                    findflag = 1;
                    printf("%d\n", o.dist + dist[u.index()] + 1);
                    return;
                }
                if (usedA[u.index()] == cases)
                    return;
                u.dist = o.dist + 1;
                usedA[u.index()] = cases, dist[u.index()] = u.dist;
                QA.push(u);
            } else {
                if (usedA[u.index()] == cases) {
                    findflag = 1;
                    printf("%d\n", o.dist + dist[u.index()] + 1);
                    return;
                }
                if (usedB[u.index()] == cases)
                    return;
                u.dist = o.dist + 1;
                usedB[u.index()] = cases, dist[u.index()] = u.dist;
                QB.push(u);
            }
        }
        return ;
    }
    int x = u.c[idx];
    for (int i = 0; i < g[x].size(); i++) {
        u.c[idx] = g[x][i];
        dfs(u, o, idx+1, dir);
    }
}
void bfs(state st, state ed) {
    cases++, findflag = 0;
    while (!QA.empty())  QA.pop();
    while (!QB.empty())  QB.pop();
    state u;
    st.dist = 0, ed.dist = 0;
    QA.push(st), usedA[st.index()] = cases;
    QB.push(ed), usedB[ed.index()] = cases;
    while (!QA.empty() || !QB.empty()) {
        if (QB.empty() || QA.front().dist <= QB.front().dist) {
            u = QA.front(), QA.pop();
            dfs(u, u, 0, 0);
        } else {
            u = QB.front(), QB.pop();
            dfs(u, u, 0, 1);
        }
        if (findflag)
            return;
    }
    puts("-1");
}
int main() {
    while (scanf("%d %d %d", &M, &N, &K) == 3) {
        if (M == 0 && N == 0 && K == 0)
            break;
        while (getchar() != '\n');
        for (int i = 0; i < N; i++)
            gets(cg[i]);
        for (int i = 0; i < N * M; i++)
            g[i].clear();
        
        int A[MAXN][MAXN], label = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (cg[i][j] != '#') {
                    A[i][j] = label++;
                }
            }
        }
        
        state st, ed;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (cg[i][j] >= 'a' && cg[i][j] <= 'z') {
                    st.c[cg[i][j] - 'a'] = A[i][j];
                    cg[i][j] = ' ';
                }
                if (cg[i][j] >= 'A' && cg[i][j] <= 'Z') {
                    ed.c[cg[i][j] - 'A'] = A[i][j];
                    cg[i][j] = ' ';
                }
            }
        }
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (cg[i][j] == ' ') {
                    int tx, ty;
                    for (int k = 0; k < 4; k++) {
                        tx = i + dx[k], ty = j + dy[k];
                        if (isValidPos(tx, ty))
                            g[A[i][j]].push_back(A[tx][ty]);
                    }
                    g[A[i][j]].push_back(A[i][j]); // itself
                }
            }
        }
        bfs(st, ed);
    }
    return 0;
}
/*
 
*/