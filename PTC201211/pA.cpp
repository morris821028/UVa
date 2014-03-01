#include <stdio.h>
#include <string.h>
struct mx {
    unsigned char v[55][55];
};
mx mult(mx A, mx B, int a, int b, int c){
    mx C;
    int i, j, k;
    memset(&C, 0, sizeof(C));
    for(i = 0; i < a; i++) {
        for(j = 0; j < c; j++) {
            for(k = 0; k < b; k++)
                C.v[i][j] += A.v[i][k]*B.v[k][j];
        }
    }
    return C;
}
mx A[855], B, one;
int M, N, K, S, E;
/*
3 2 1
10 100 200 255
8 6 2 3
1 0 0 1
1 0 2 8
*/
int main() {
    int i, j, k, x;
    memset(&one, 0, sizeof(one));
    for(i = 0; i < 55; i++)
        one.v[i][i] = 1;
    while(scanf("%d %d %d", &M, &N, &K) == 3) {
        for(i = 0; i < M; i++) {
            for(j = 0; j < N; j++)
                for(k = 0; k < N; k++) {
                    scanf("%d", &x);
                    A[i].v[j][k] = (unsigned char)x;
                }
        }
        mx ans;
        while(K--) {
            scanf("%d %d", &S, &E);
            for(i = 0; i < N; i++) {
                scanf("%d", &x);
                B.v[i][0] = x;
            }
            ans = B;
            if(S <= E) {
                for(i = E; i >= S; i--)
                ans = mult(A[i], ans, N, N, 1);
            } else {
                for(i = E; i >= 0; i--)
                ans = mult(A[i], ans, N, N, 1);
                for(i = M-1; i >= S; i--)
                ans = mult(A[i], ans, N, N, 1);
            }
            for(i = 0; i < N; i++) {
                if(i)
                    printf(" ");
                printf("%d", ans.v[i][0]);
            }
            puts("");
        }
    }
    return 0;
}
