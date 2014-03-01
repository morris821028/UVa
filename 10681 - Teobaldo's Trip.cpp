#include <stdio.h>
#include <string.h>
struct Mtx {
    char v[100][100];
};
Mtx mult(Mtx& A, Mtx& B, int n) {
    static int i, j, k;
    static Mtx C;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            C.v[i][j] = 0;
            for(k = 0; k < n; k++) {
                C.v[i][j] |= A.v[i][k]&B.v[k][j];
            }
        }
    }
    return C;
}
Mtx A;
void sol(int s, int e, int d, int n) {
    static Mtx x, y;
    static int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            x.v[i][j] = 0;
            y.v[i][j] = A.v[i][j];
        }
        x.v[i][i] = 1;
    }
    while(d) {
        if(d&1)
            x = mult(x, y, n);
        y = mult(y, y, n);
        d >>= 1;
    }
    if(x.v[s][e])
        puts("Yes, Teobaldo can travel.");
    else
        puts("No, Teobaldo can not travel.");
}
int main() {
    int C, L, x, y, s, e, d;
    while(scanf("%d %d", &C, &L) == 2) {
        if(!C && !L)    break;
        memset(&A, 0, sizeof(A));
        while(L--) {
            scanf("%d %d", &x, &y);
            x--, y--;
            A.v[x][y] = 1;
            A.v[y][x] = 1;
        }
        scanf("%d %d %d", &s, &e, &d);
        s--, e--;
        sol(s, e, d, C);
    }
    return 0;
}
