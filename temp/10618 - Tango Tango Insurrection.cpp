#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
using namespace std;
#define MAXN 128
#define INF 0x3f3f3f3f
int dp[MAXN][4][4][3];  // [i-step][left-foot][right-foot][last-foot]
struct Node {
    int LR;
    Node *prev;
    Node(Node *p = NULL, int s = 0):
    prev(p), LR(s) {}
} from[MAXN][4][4][3];
enum DIR {UP, LEFT, RIGHT, DOWN, DOT};
int toDIR(char c) {
    switch (c) {
        case 'U':   return UP;
        case 'L':   return LEFT;
        case 'R':   return RIGHT;
        case 'D':   return DOWN;
        case '.':   return DOT;
    }
    assert(false);
}
int moveCost(int from, int to) {
    if (from == to)     return 3;
    if (from + to == 3) return 7; // moves directly across
    return 5; // moves to adjacent
}
void update(int step, int l, int r, int prev, int kind) {
    int val = dp[step][l][r][prev];
    Node *u = &from[step][l][r][prev];
    int banL[4] = {}, banR[4] = {};
    if ((r == UP || r == DOWN) && l == RIGHT)
        banR[0] = banR[1] = banR[2] = banR[3] = 1, banR[r] = 0;
    if ((l == UP || l == DOWN) && r == LEFT)
        banL[0] = banL[1] = banL[2] = banL[3] = 1, banL[l] = 0;
    
    if (kind == DOT) {
        if (dp[step+1][l][r][0] > val) { // no move
            dp[step+1][l][r][0] = val;
            from[step+1][l][r][0] = Node(u, DOT);
        }
        for (int i = 0; i < 4; i++) { // move left foot
            if (banL[i])  continue;
            if (i == l || i == r)   continue;
            int w = 0;
            if (prev == LEFT)   w = moveCost(l, i);
            else                w = 1;
            if (dp[step+1][i][r][LEFT] > val + w) {
                dp[step+1][i][r][LEFT] = val + w;
                from[step+1][i][r][LEFT] = Node(u, LEFT);
            }
        }
        for (int i = 0; i < 4; i++) { // move right foot
            if (banR[i])  continue;
            if (i == l || i == r)   continue;
            int w = 0;
            if (prev == RIGHT)  w = moveCost(r, i);
            else                w = 1;
            if (dp[step+1][l][i][RIGHT] > val + w) {
                dp[step+1][l][i][RIGHT] = val + w;
                from[step+1][l][i][RIGHT] = Node(u, RIGHT);
            }
        }
    } else {
        for (int i = 0; i < 4; i++) { // move left foot
            if (banL[i])  continue;
            if (i == r)   continue;
            int w = 0;
            if (prev == LEFT)   w = moveCost(l, i);
            else                w = 1;
            if (i != kind)
                continue;
            if (dp[step+1][i][r][LEFT] > val + w) {
                dp[step+1][i][r][LEFT] = val + w;
                from[step+1][i][r][LEFT] = Node(u, LEFT);
            }
        }
        for (int i = 0; i < 4; i++) { // move right foot
            if (banR[i])  continue;
            if (i == l)   continue;
            int w = 0;
            if (prev == RIGHT)  w = moveCost(r, i);
            else                w = 1;
            if (i != kind)
                continue;
            if (dp[step+1][l][i][RIGHT] > val + w) {
                dp[step+1][l][i][RIGHT] = val + w;
                from[step+1][l][i][RIGHT] = Node(u, RIGHT);
            }
        }
    }
}
int main() {
    char s[1024];
    while (scanf("%s", s) == 1 && s[0] != '#') {
        int N = (int) strlen(s);
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    for (int l = 0; l < 3; l++) {
                        dp[i][j][k][l] = INF;
                    }
                }
            }
        }
        dp[0][LEFT][RIGHT][0] = 0, from[0][LEFT][RIGHT][0].prev = NULL;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    if (j == k) // same pos
                        continue;
                    for (int l = 0; l < 3; l++) {
                        if (dp[i][j][k][l] == INF)
                            continue;
//                        printf("%d %d %d %d - %d\n", i, j, k, l, dp[i][j][k][l]);
//                        getchar();
                        update(i, j, k, l, toDIR(s[i]));
                    }
                }
            }
        }
        int mn = 0x3f3f3f3f;
        Node *p = NULL;
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (j == k) // same pos
                    continue;
                for (int l = 0; l < 3; l++) {
                    if (dp[N][j][k][l] < mn) {
                        mn = dp[N][j][k][l];
                        p = &from[N][j][k][l];
                    }
                }
            }
        }
        string ret = "";
        while (p && p->prev) {
            ret = (p->LR == DOT ? '.' : (p->LR == LEFT ? 'L' : 'R')) + ret;
            p = p->prev;
        }
//        printf("%d\n", mn);
        printf("%s\n", ret.c_str());
    }
    return 0;
}
/*
 DLU.LDUDRL
 RURD.RURLL
 RDRLRUDLUU
 RD.DLDR.DR
 UURLLLDR.D
 .URDLLRD..
 ..RLUL.L.D
 .DULR.RRDL
 LLU..LD.L.
 DDLRURRDDL
 RRRURRD..D
 .UUUDUDRUL
 R.UU.DL.UD
 DRDL.LRDRL
 UL...RUUU.
 LDRURUURLL
 ..RD...RR.
 .R.LDLL.LR
 UUUL.LRULD
 L.D.LLURRU
 #
*/