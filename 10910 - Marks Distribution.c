#include <stdio.h>

int main() {
    int pascal[100][100] = {};
    int i, j;
    pascal[0][0] = 1;
    for(i = 1; i < 100; i++) {
        pascal[i][0] = 1;
        for(j = 1; j <= i; j++) {
            pascal[i][j] = pascal[i-1][j]+pascal[i-1][j-1];
        }
    }
    int tt, n, t, p;
    scanf("%d", &tt);
    while(tt--) {
        scanf("%d %d %d", &n, &t, &p);
        if(t < n*p)
            puts("0");
        else
            printf("%d\n", pascal[t-n*p+n-1][n-1]);
    }
    return 0;
}
