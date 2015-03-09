#include <stdio.h>
int g[1000][1000];
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, i, j;
        scanf("%d", &n);
        long long ans = (long long)(n-1)*n/2*(n-2), sum = 0;
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                scanf("%d", &g[i][j]);
                g[j][i] = g[i][j];
            }
            long long r = 0, b = 0;
            for(j = 0; j < n; j++) {
                if(i == j)  continue;
                if(g[i][j] == 0)    b++;
                else    r++;
            }
            sum = sum + (long long)r*b;
        }
        ans = ans - sum*3/2;
        printf("%lld\n", ans/3);
    }
    return 0;
}/*
3

*/
