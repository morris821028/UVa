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
char sa[8], sb[8], sc[8];
int Alen, Blen, Clen;
#define HASH_MOD 1000003
struct State {
    int a[3], b[3], c[5];
    State() {
        for (int i = 0; i < 3; i++)
            a[i] = b[i] = -2;
        for (int i = 0; i < 5; i++)
            c[i] = -2;
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
State retState;
int mnChange, mx_depth;
void dfs(int idx, State &u, int change) {
    if (change >= mnChange || change >= mx_depth)
        return ;
    if (mnChange != 0x3f3f3f3f)
        return;
    if (idx == 2 + 2 + 4) {
        if (R[u.hash()][u] == 1) {
            mnChange = change;
            retState = u;
        }
        return;
    }
    if (idx < 2) {
        if (u.a[idx] >= 0) {
            int t = u.a[idx];
            u.a[idx] = -1;
            dfs(idx+1, u, change+1);
            u.a[idx] = t;
        } else {
            dfs(idx+1, u, change);
        }
        if (u.a[idx] == -2) {
            dfs(idx+1, u, change);
        } else {
            for (int i = idx == 0; i < 10; i++) {
                int t = u.a[idx];
                u.a[idx] = i;
                dfs(idx+1, u, change+(t != i));
                u.a[idx] = t;
            }
        }
    } else if (idx < 4) {
        if (u.b[idx-2] >= 0) {
            int t = u.b[idx-2];
            u.b[idx-2] = -1;
            dfs(idx+1, u, change+1);
            u.b[idx-2] = t;
        } else {
            dfs(idx+1, u, change);
        }
        if (u.b[idx-2] == -2) {
            dfs(idx+1, u, change);
        } else {
            for (int i = idx == 2; i < 10; i++) {
                int t = u.b[idx-2];
                u.b[idx-2] = i;
                dfs(idx+1, u, change+(t != i));
                u.b[idx-2] = t;
            }
        }
    } else {
        if (u.c[idx-4] >= 0) {
            int t = u.c[idx-4];
            u.c[idx-4] = -1;
            dfs(idx+1, u, change+1);
            u.c[idx-4] = t;
        } else {
            dfs(idx+1, u, change);
        }
        if (u.c[idx-4] == -2) {
            dfs(idx+1, u, change);
        } else {
            for (int i = idx == 4; i < 10; i++) {
                int t = u.c[idx-4];
                u.c[idx-4] = i;
                dfs(idx+1, u, change+(t != i));
                u.c[idx-4] = t;
            }
        }
    }
}
int test(State &st) {
    return R[st.hash()][st] == 1;
}
void solv(State st) {
    if (test(st)) {
        printState(st);
        return ;
    }
    mnChange = 0x3f3f3f3f;
    for (mx_depth = 0; mx_depth <= mnChange; mx_depth++)
        dfs(0, st, 0);
    printState(retState);
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
        solv(st);
    }
    return 0;
}
/*
 7 ** 8*
 ** ** ***
 ** ** ****
 0
*/