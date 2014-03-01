#include <stdio.h>
#define FOR(i,n) for(i=0;i<n;i++)
#define LL long long
#define N 505
LL A[N][N], B[N][N], C[N][N], R[N], D[N], E[N];
int n, i, j;
int solve() {
    FOR(i,n)
        R[i] = i+1, D[i] = E[i] = 0;
    FOR(i,n)FOR(j,n)
        E[i] += C[i][j]*R[j];
    FOR(i,n)FOR(j,n)
        D[i] += B[i][j]*R[j];
    FOR(i,n)    R[i] = 0;
    FOR(i,n)FOR(j,n)
        R[i] += A[i][j]*D[j];
    FOR(i,n)
        if(R[i] != E[i])
            return 0;
    return 1;
}
LL ReadInt(LL *x) {
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
    while(scanf("%d", &n) == 1) {
        FOR(i,n)FOR(j,n)
            ReadInt(&A[i][j]);
        FOR(i,n)FOR(j,n)
            ReadInt(&B[i][j]);
        FOR(i,n)FOR(j,n)
            ReadInt(&C[i][j]);
        if(solve())
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
