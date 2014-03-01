#include <stdio.h>
#include <math.h>
#define eps 1e-7
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int m = 2*n, i, j, k, ch;
        double mx[n][m], tmp, c;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++)
                scanf("%lf", &mx[i][j]);
            for(j = n; j < m; j++)
                mx[i][j] = 0;
            mx[i][i+n] = 1;
        }
        for(i = 0; i < n; i++) {
            if(fabs(mx[i][i]) < eps)  break;
            for(j = 0; j < n; j++) {
                if(i == j)  continue;
                c = mx[j][i]/mx[i][i];
                for(k = i; k < m; k++)
                    mx[j][k] = mx[j][k] - mx[i][k]*c;
            }
        }
        if(i != n) {
            puts("Not possible\n");
            continue;
        }
        for(i = 0; i < n; i++, puts("")) {
            for(j = n; j < m; j++) {
                if(j != n)  putchar(' ');
                printf("%.6lf", mx[i][j]/mx[i][i]);
            }
        }
        puts("");
    }
    return 0;
}
