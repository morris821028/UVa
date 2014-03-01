#include<stdio.h>
#include<stdlib.h>

int main() {
    int a, b, c, d;
    while(scanf("%d %d %d %d", &a, &b, &c, &d) == 4) {
        if(b != c) {
            puts("Error");
            continue;
        }
        int i, j, k;
        long long A[101][101], B[101][101], sum;
        for(i = 0; i < a; i++)
            for(j = 0; j < b; j++)
                scanf("%lld", &A[i][j]);
        for(i = 0; i < c; i++)
            for(j = 0; j < d; j++)
                scanf("%lld", &B[i][j]);
        for(i = 0; i < a; i++) {
            for(j = 0; j < d; j++) {
                sum = 0;
                for(k = 0; k < c; k++)
                    sum += A[i][k]*B[k][j];
                printf("%lld ", sum);
            }
            puts("");
        }
    }
    return 0;
}
