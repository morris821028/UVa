#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
#include <assert.h>
using namespace std;

char table[100][100][10], stable[10000][10];
int tableLen[100][100], stableLen[10000];
vector< pair<int, int> > C[10000];
char sa[8], sb[8], sc[8];
int Alen, Blen, Clen;
#define HASH_MOD 100003
struct State {
    int a[3], b[3], c[5];
    int dist;
    State() {
        for (int i = 0; i < 3; i++)
            a[i] = b[i] = -2;
        for (int i = 0; i < 5; i++)
            c[i] = -2;
        dist = 0;
    }
    bool operator<(const State &y) const {
        for (int i = 0; i < 2; i++)
            if (a[i] != y.a[i])
                return a[i] > y.a[i];
        for (int i = 0; i < 2; i++)
            if (b[i] != y.b[i])
                return b[i] > y.b[i];
        for (int i = 0; i < 4; i++)
            if (c[i] != y.c[i])
                return c[i] > y.c[i];
        return false;
    }
    unsigned int hash() {
        unsigned int va = 63689, vb = 378551;
        unsigned int value = 0;
        for (int i = 0; i < 2; i++) {
            value = value * va + a[i];
            va *= vb;
        }
        for (int i = 0; i < 2; i++) {
            value = value * va + b[i];
            va *= vb;
        }
        for (int i = 0; i < 4; i++) {
            value = value * va + c[i];
            va *= vb;
        }
        return value % HASH_MOD;
    }
};
struct cmp {
    bool operator() (const State &x, const State &y) const {
        if (x.dist != y.dist)
            return x.dist > y.dist;
        for (int i = 0; i < Alen; i++)
            if (x.a[i] != y.a[i])
                return x.a[i] > y.a[i];
        for (int i = 0; i < Blen; i++)
            if (x.b[i] != y.b[i])
                return x.b[i] > y.b[i];
        for (int i = 0; i < Clen; i++)
            if (x.c[i] != y.c[i])
                return x.c[i] > y.c[i];
        return false;
    }
};
map<State, int> R[HASH_MOD];
void printState(State u) {
    for (int i = 0; i < 2; i++) {
        if (u.a[i] == -2)
            break;
        printf("%c", u.a[i] == -1 ? '*' : u.a[i] + '0');
    }
    printf(" ");
    for (int i = 0; i < 2; i++) {
        if (u.b[i] == -2)
            break;
        printf("%c", u.b[i] == -1 ? '*' : u.b[i] + '0');
    }
    printf(" ");
    for (int i = 0; i < 4; i++) {
        if (u.c[i] == -2)
            break;
        printf("%c", u.c[i] == -1 ? '*' : u.c[i] + '0');
    }
    puts("");
}
int fuzzyMatch(int x, int a[], int alen) {
    if (stableLen[x] != alen)
        return false;
    for (int i = 0; i < alen; i++) {
        if (a[i] == -1)
            continue;
        if (stable[x][i] != a[i] + '0')
            return 0;
    }
    return 1;
}
int checkSolution(State st) {
    int sol = R[st.hash()][st];
    return sol == 1;
}
set<State, cmp> used[HASH_MOD];
void bfs(State st) {
    for (int i = 0; i < HASH_MOD; i++)
        used[i].clear();
    priority_queue<State, vector<State>, cmp> pQ;
    if (checkSolution(st)) {
        printState(st);
        return ;
    }
    st.dist = 0;
    pQ.push(st), used[st.hash()].insert(st);
    State u, v;
    while (!pQ.empty()) {
        u = pQ.top(), pQ.pop();
        if (checkSolution(u)) {
            printState(u);
            return ;
        }
        for (int i = 0; i < Alen; i++) {
            if (u.a[i] != -1) {
                v = u;
                v.a[i] = -1, v.dist = u.dist + 1;
                if (used[v.hash()].count(v))
                    continue;
                used[v.hash()].insert(v), pQ.push(v);
            }
                for (int j = i == 0; j < 10; j++) {
                    v = u;
                    v.a[i] = j, v.dist = u.dist + 1;
                    if (used[v.hash()].count(v))
                        continue;
                    used[v.hash()].insert(v), pQ.push(v);
                }
        }
        // b
        for (int i = 0; i < Blen; i++) {
            if (u.b[i] != -1) {
                v = u;
                v.b[i] = -1, v.dist = u.dist + 1;
                if (used[v.hash()].count(v))
                    continue;
                used[v.hash()].insert(v), pQ.push(v);
            }
                for (int j = i == 0; j < 10; j++) {
                    v = u;
                    v.b[i] = j, v.dist = u.dist + 1;
                    if (used[v.hash()].count(v))
                        continue;
                    used[v.hash()].insert(v), pQ.push(v);
                }
        }
        // c
        for (int i = 0; i < Clen; i++) {
            if (u.c[i] != -1) {
                v = u;
                v.c[i] = -1, v.dist = u.dist + 1;
                if (used[v.hash()].count(v))
                    continue;
                used[v.hash()].insert(v), pQ.push(v);
            }
                for (int j = i == 0; j < 10; j++) {
                    v = u;
                    v.c[i] = j, v.dist = u.dist + 1;
                    if (used[v.hash()].count(v))
                        continue;
                    used[v.hash()].insert(v), pQ.push(v);
                }
        }
    }
}
void fuzzyBuild(int idx, State &u) {
    if (idx == Alen + Blen + Clen) {
        R[u.hash()][u]++;
        return;
    }
    if (idx < 2) {
        if (u.a[idx] >= 0) {
            int t = u.a[idx];
            u.a[idx] = -1;
            fuzzyBuild(idx+1, u);
            u.a[idx] = t;
        }
        fuzzyBuild(idx+1, u);
    } else if (idx < 4) {
        if (u.b[idx-2] >= 0) {
            int t = u.b[idx-2];
            u.b[idx-2] = -1;
            fuzzyBuild(idx+1, u);
            u.b[idx-2] = t;
        }
        fuzzyBuild(idx+1, u);
    } else {
        if (u.c[idx-4] >= 0) {
            int t = u.c[idx-4];
            u.c[idx-4] = -1;
            fuzzyBuild(idx+1, u);
            u.c[idx-4] = t;
        }
        fuzzyBuild(idx+1, u);
    }
}
int main() {
    Alen = 2, Blen = 2, Clen = 4;
    for (int i = 1; i < 10000; i++) {
        sprintf(stable[i], "%d", i);
        stableLen[i] = (int) strlen(stable[i]);
    }
    for (int i = 1; i < 100; i++) {
        for (int j = 1; j < 100; j++) {
            sprintf(table[i][j], "%d", i * j);
            tableLen[i][j] = (int) strlen(table[i][j]);
            C[i*j].push_back(make_pair(i, j));
            State u;
            for (int k = 0; k < stableLen[i]; k++)
                u.a[k] = stable[i][k] - '0';
            for (int k = 0; k < stableLen[j]; k++)
                u.b[k] = stable[j][k] - '0';
            for (int k = 0; k < stableLen[i*j]; k++)
                u.c[k] = stable[i*j][k] - '0';
            u.a[stableLen[i]] = u.b[stableLen[j]] = -2;
            u.c[stableLen[i*j]] = -2;
            fuzzyBuild(0, u);
        }
    }
    
    int cases = 0;
    while (scanf("%s %s %s", sa, sb, sc) == 3) {
        Alen = (int) strlen(sa);
        Blen = (int) strlen(sb);
        Clen = (int) strlen(sc);
        printf("Case %d: ", ++cases);
        State st;
        for (int i = 0; i < Alen; i++)
            st.a[i] = sa[i] == '*' ? -1 : sa[i] - '0';
        for (int i = 0; i < Blen; i++)
            st.b[i] = sb[i] == '*' ? -1 : sb[i] - '0';
        for (int i = 0; i < Clen; i++)
            st.c[i] = sc[i] == '*' ? -1 : sc[i] - '0';
        bfs(st);
    }
    return 0;
}
/*
 7 ** 8*
 ** ** ***
 ** ** ****
 0
*/