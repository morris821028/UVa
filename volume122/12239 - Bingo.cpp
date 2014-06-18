#include <stdio.h>
#include <stdlib.h>
int main() {
    int n, m, A[105];
    int i, j, k;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        for(i = 0; i < m; i++)
            scanf("%d", &A[i]);
        int mark[105] = {};
        for(i = 0; i < m; i++)
            for(j = i; j < m; j++)
                mark[abs(A[i]-A[j])] = 1;
        k = 1;
        for(i = 0; i <= n && k; i++)
            k &= mark[i];
        puts(k ? "Y" : "N");
    }
    return 0;
}
