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
int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};
int invShift[8] = {5, 4, 7, 6, 1, 0, 3, 2};
void shiftStrip(int A[], int dir) {
    int tmp = A[shift[dir][0]];
    for (int i = 0; i < 6; i++)
        A[shift[dir][i]] = A[shift[dir][i+1]];
    A[shift[dir][6]] = tmp;
}

int H(int A[]) {
    int K[4] = {};
    for (int i = 0; i < 8; i++) {
        K[A[center[i]]]++;
    }
    return 8 - max(K[1], max(K[2], K[3]));
}
int ida_depth, solved;
int path[128];
int IDA(int A[], int dep, int hv) {
    if (hv == 0) {
        solved = 1;
        if (dep == 0) {
            puts("No moves needed");
        } else {
            for (int i = 0; i < dep; i++)
                printf("%c", path[i] + 'A');
            puts("");
        }
        printf("%d\n", A[center[0]]);
        return dep;
    }
    if (dep + hv > ida_depth)
        return dep + hv;
    int back = 0x3f3f3f3f, shv, tmp;
    for (int i = 0; i < 8; i++) {
        shiftStrip(A, i);
        shv = H(A), path[dep] = i;
        tmp = IDA(A, dep + 1, shv);
        back = min(back, tmp);
        shiftStrip(A, invShift[i]);
        if (solved) return back;
    }
    return back;
}

int main() {
    while (true) {
        int A[32];
        for (int i = 0; i < 24; i++) {
            scanf("%d", &A[i]);
            if (A[i] == 0)  return 0;
        }
        solved = 0;
        for (ida_depth = 0; solved == 0;)
            ida_depth = IDA(A, 0, H(A));
    }
    return 0;
}
/*
 
*/