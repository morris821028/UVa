#include <stdio.h>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <string.h>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXSTATE 1048576
#define MAXN (20000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXN];
// 24! / (8! 16!) = 735471
int shift[8][8] = {
    {0, 2, 6, 11, 15, 20, 22},      // A
    {1, 3, 8, 12, 17, 21, 23},      // B
    {10, 9, 8, 7, 6, 5, 4},         // C
    {19, 18, 17, 16, 15, 14, 13},   // D
    {23, 21, 17, 12, 8, 3, 1},      // E
    {22, 20, 15, 11, 6, 2, 0},      // F
    {13, 14, 15, 16, 17, 18, 19},   // G
    {4, 5, 6, 7, 8, 9, 10}          // H
};
int hcost[24] = {2, 2, 1, 1, 2, 1, 0, 0, 0, 1, 2, 0, 0, 2, 1, 0, 0, 0, 1, 2, 1, 1, 2, 2};
int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

struct state {
    int v, dir, dist, kind;
    state *prev;
} states[MAXSTATE];
int stateSize;
void shiftStrip(int A[], int dir) { // inv shift
    int tmp = A[shift[dir][0]];
    for (int i = 0; i < 6; i++)
        A[shift[dir][i]] = A[shift[dir][i+1]];
    A[shift[dir][6]] = tmp;
}
int toBit(int A[]) {
    int ret = 0;
    for (int i = 0; i < 24; i++)
        ret |= (A[i]&1)<<i;
    return ret;
}
void toArr(int v, int A[]) {
    for (int i = 0; i < 24; i++)
        A[i] = (v>>i)&1;
}
int H(int A[]) {
    int ret = 0x3f3f3f3f;
    for (int i = 0; i < 24; i++) {
        if (A[i])
            ret = min(ret, hcost[i]);
    }
    return ret;
}
string bfs(int K1[], int K2[], int K3[], int &retVal) {
    memset(mark, 0, sizeof(mark));
    int A[32] = {}, B[32] = {}, finalState = 0;
    for (int i = 0; i < 8; i++)
        B[center[i]] = 1;
    finalState = toBit(B);
    queue<state*> Q;
    state *st, *u, *v;
    stateSize = 0;
    st = &states[stateSize++];
    st->v = toBit(K1), st->prev = NULL, st->dist = 0, st->kind = 1;
    Q.push(st), SET(st->v);
    st = &states[stateSize++];
    st->v = toBit(K2), st->prev = NULL, st->dist = 0, st->kind = 2;
    Q.push(st), SET(st->v);
    st = &states[stateSize++];
    st->v = toBit(K3), st->prev = NULL, st->dist = 0, st->kind = 3;
    Q.push(st), SET(st->v);
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        
        if (u->v == finalState) {
            string ret = "";
            retVal = u->kind;
            while (u->prev) {
                ret = (char)('A' + u->dir) + ret;
                u = u->prev;
            }
            return ret;
        }
        toArr(u->v, A);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 24; j++)
                B[j] = A[j];
            shiftStrip(B, i);
            int val = toBit(B);
            if (GET(val))
                continue;
            v = &states[stateSize++];
            v->v = val, v->prev = u, v->dir = i, v->dist = u->dist + 1, v->kind = u->kind;
            SET(val);
            Q.push(v);
        }
    }
    return "-";
}

int main() {
    while (true) {
        int A[32];
        for (int i = 0; i < 24; i++) {
            scanf("%d", &A[i]);
            if (A[i] == 0)  return 0;
        }
        
        string ret = "";
        int retVal = -1;
        int K1[32], K2[32], K3[32];
        for (int i = 0; i < 24; i++) {
            K1[i] = A[i] == 1;
            K2[i] = A[i] == 2;
            K3[i] = A[i] == 3;
        }
        ret = bfs(K1, K2, K3, retVal);
        if (ret.length() == 0) {
            puts("No moves needed");
        } else {
            puts(ret.c_str());
        }
        printf("%d\n", retVal);
    }
    return 0;
}
/*
 
*/