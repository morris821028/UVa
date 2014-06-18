#include <stdio.h>
int root[105][105];
char bits[105];
void dfs(int l, int r, int dep) {
    if(l > r) {
        bits[dep] = '\0';
        puts(bits);
        return;
    }
    bits[dep] = '0';
    dfs(l, root[l][r]-1, dep+1);
    bits[dep] = '1';
    dfs(root[l][r]+1, r, dep+1);
}
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        double q[105] = {}, tmp;
        double w[105][105] = {}, e[105][105];
        int l, i, j, r;
        for(i = 0; i < n; i++)
            scanf("%lf", &q[i]);
        n--;
        for(i = 1; i <= n+1; i++)
            e[i][i-1] = w[i][i-1] = q[i-1];
        for(l = 1; l <= n; l++) {
            for(i = 1; i <= n-l+1; i++) {
                j = i+l-1;
                e[i][j] = 32767;
                w[i][j] = w[i][j-1]+q[j];
                for(r = i; r <= j; r++) {
                    tmp = e[i][r-1]+e[r+1][j]+w[i][j];
                    if(tmp < e[i][j]) {
                        e[i][j] = tmp;
                        root[i][j] = r;
                    }
                }
            }
        }
        printf("%.4lf\n", e[1][n]-w[1][n]);
        dfs(1, n, 0);
    }
    return 0;
}
