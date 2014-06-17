#include <stdio.h>
int A[1005][1005];
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, m, i, j, first = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                ReadInt(&A[i][j]);
        if(first++)   puts("");
        int B[1005] = {}, sum = 0;
        int tot = 0;
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                B[i] += A[j][i];
        for(i = 0; i < m; i++)
            sum += B[i];
        for(i = m-1; i < n; i++) {
            for(j = 0; j <= n-m; j++) {
                printf("%d\n", sum);
                tot += sum;
                sum = sum - B[j] + B[j+m];
            }
            for(j = 0; j < n; j++)
                B[j] = B[j] - A[i-m+1][j] + A[i+1][j];
            for(j = 0, sum = 0; j < m; j++)
                sum += B[j];
        }
        printf("%d\n", tot);
    }
    return 0;
}
