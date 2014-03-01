#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
long long V3[21][21][21], V2[21][21][21];
void sol(int A, int B, int C) {
    long long mx = V3[0][0][0];
    int i, j, k, p, q;
    for(i = 0; i < A; i++)
        for(j = 0; j < B; j++)
            for(k = 0; k < C; k++)
                mx = max(mx, V3[i][j][k]);
    for(p = 0; p < A; p++)
    for(q = p; q < A; q++) {
        for(i = 0; i < B; i++) {
            long long sum[21] = {}, tmp;
            for(j = i; j < B; j++) {
                tmp = 0;
                for(k = 0; k < C; k++) {
                    sum[k] += V2[q][j][k];
                    if(p)   sum[k] -= V2[p-1][j][k];
                    tmp += sum[k];
                    mx = max(mx, tmp);
                    if(tmp < 0) tmp = 0;
                }
            }
        }
    }
    printf("%lld\n", mx);
}
int main() {
    int testcase, A, B, C;
    int i, j, k;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &A, &B, &C);
        memset(V2, 0, sizeof(V2));
        for(i = 0; i < A; i++) {
            for(j = 0; j < B; j++) {
                for(k = 0; k < C; k++) {
                    scanf("%lld", &V3[i][j][k]);
                    V2[i][j][k] = V3[i][j][k];
                    if(i)   V2[i][j][k] += V2[i-1][j][k];
                }
            }
        }
        sol(A, B, C);
        if(testcase)
            puts("");
    }
    return 0;
}
/*
1
2 3 3
21 -39 4 -39 4 -44 1 -32 -25 -35 2 17 6 10 2 -12 -22 35
*/
