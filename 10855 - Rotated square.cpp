#include <stdio.h>
#include <string.h>
char big[500][500], small[500][500];
int find(int n, int m) {
    int ans = 0, i, j, k, l;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i+m <= n && j+m <= n) {
                int cnt = 0;
                for(k = 0; k < m; k++) {
                    for(l = 0; l < m; l++) {
                        if(big[i+k][j+l] == small[k][l])
                            cnt++;
                    }
                }
                if(cnt == m*m)
                    ans++;
            }
        }
    }
    return ans;
}
void rotate(int n) {
    char tmp[n][n];
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
            tmp[i][j] = small[n-j-1][i];
    }
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
           small[i][j] = tmp[i][j];
    }
}
int main() {
    int n, m, i;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        for(i = 0; i < n; i++)
            scanf("%s", big[i]);
        for(i = 0; i < m; i++)
            scanf("%s", small[i]);
        for(i = 0; i < 4; i++) {
            if(i)
                putchar(' ');
            printf("%d", find(n, m));
            rotate(m);
        }
        puts("");
    }
    return 0;
}
