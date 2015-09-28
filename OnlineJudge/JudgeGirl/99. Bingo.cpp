#include <stdio.h>
char name[16][128];
int g[16][256][256], RM[16][131072][2], A[65536];
int n, m;
int isvalid(int x, int y) {
    return x >= 0 && y >= 0 && x < m && y < m;
}
int bingo(int idx, int x, int y) {
    const int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
    const int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};
    for (int i = 0; i < 8; i += 2) {
        int cnt = 0, tx, ty;
        tx = x, ty = y;
        for ( ; isvalid(tx, ty) && g[idx][tx][ty] == 0; cnt++)
            tx += dx[i], ty += dy[i];
        tx = x, ty = y;
        for ( ; isvalid(tx, ty) && g[idx][tx][ty] == 0; cnt++)
            tx += dx[i+1], ty += dy[i+1];
        if (cnt == m+1) return 1;
    }
    return 0;
}
int main() {
    int x;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 0; i < n; i++) {
            scanf("%s", name[i]);
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m; k++) {
                    scanf("%d", &g[i][j][k]);
                    RM[i][g[i][j][k]][0] = j;
                    RM[i][g[i][j][k]][1] = k;
                }
            }
        }
        
        for (int i = 0; i < m*m; i++)
            scanf("%d", &A[i]);
        
        for (int it = 0; it < m*m; it++) {
            x = A[it];
            int has = 0;
            for (int i = 0; i < n; i++) {
                g[i][RM[i][x][0]][RM[i][x][1]] = 0;
                int f = bingo(i, RM[i][x][0], RM[i][x][1]);
                has |= f;
                
            }
            if (has == 1) {
                printf("%d", x);
                for (int i = 0; i < n; i++) {
                    int f = bingo(i, RM[i][x][0], RM[i][x][1]);
                    if (f)  printf(" %s", name[i]);
                }
                puts("");
                break;
            }
        }
    }
    return 0;
}
/*
 2 3
 Alice
 1 2 3
 4 5 6
 7 8 9
 Blob
 1 2 3
 4 5 6
 7 8 9
 1 2 4 8 6 3 9 5 7
*/