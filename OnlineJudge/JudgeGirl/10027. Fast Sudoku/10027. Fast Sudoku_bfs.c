#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#define MAXN 65536
 
int C[81][2], N;
int R[9][3] = {}, P[MAXN*9][9][3], Pidx;
int ida_dep;
void IDA(int idx, int state[][3]) {
    if (idx == ida_dep) {
        memcpy(P[Pidx], state, sizeof(P[0])), Pidx++;
        return ;
    }
    int x = C[idx][0], y = C[idx][1];
    int c = x/3*3 + y/3;
    for (int i = 0; i < 9; i++) {
        int mask = 1<<i;
        if ((state[x][0]&mask) || (state[y][1]&mask) ||
                (state[c][2]&mask))
            continue;
        state[x][0] |= mask;
        state[y][1] |= mask;
        state[c][2] |= mask;
        IDA(idx+1, state);
        state[x][0] ^= mask;
        state[y][1] ^= mask;
        state[c][2] ^= mask;
    }
}
int dfs(int idx, int state[][3]) {
    if (idx == N)
        return 1;
    int x = C[idx][0], y = C[idx][1];
    int c = x/3*3 + y/3, sum = 0;
    for (int i = 0; i < 9; i++) {
        int mask = 1<<i;
        if ((state[x][0]&mask) || (state[y][1]&mask) ||
                (state[c][2]&mask))
            continue;
        state[x][0] |= mask;
        state[y][1] |= mask;
        state[c][2] |= mask;
        sum += dfs(idx+1, state);
        state[c][2] ^= mask;
        state[y][1] ^= mask;
        state[x][0] ^= mask;
    }
    return sum;
}
int incomplete_bfs() {
    for (ida_dep = 1; ida_dep <= N; ida_dep++) {
        Pidx = 0;
        IDA(0, R);
        if (Pidx >= MAXN)
            break;
    }
    if (ida_dep == N+1)
        return Pidx;
    int ret = 0;
    #pragma omp parallel for schedule(guided) reduction(+: ret) 
    for (int i = 0; i < Pidx; i++)
        ret += dfs(ida_dep, P[i]);
    return ret;
}
int main() {
    int g[9][9], n = 9;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);
    N = 0;
    memset(R, 0, sizeof(R));
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             if (g[i][j]) {
                 g[i][j]--;
                 R[i][0] |= 1<<g[i][j];
                 R[j][1] |= 1<<g[i][j];
                 R[i/3*3+j/3][2] |= 1<<g[i][j];
            } else {
                 C[N][0] = i, C[N][1] = j;
                 N++;
             }
         }
     }
    int ret = incomplete_bfs();
    printf("%d\n", ret);
    return 0;
}
