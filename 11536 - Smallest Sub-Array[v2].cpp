#include <stdio.h>
int X[1000005] = {0,1};
int Y[1000005] = {0,1};
int main() {
    int T, cases = 0;
    int N, M, K, i;
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d %d", &N, &M, &K);
        int modM[3005] = {};
        for(i = 0; i < 3005; i++)
            modM[i] = i%M;
        int xi1 = 3, xi2 = 2, xi3 = 1, xi;
        int idx = 2;
        int *p = &X[1], *q = &Y[1], *pp = &X[1], *qq = &Y[1];
        if(2 <= K)  *(++p) = 2, *(++q) = 2;
        if(3 <= K)  *(++p) = 3, *(++q) = 3;
        for(i = 4; i <= N; i++) {
            xi = xi1 + xi2 + xi3;
            if(xi >= M)   xi = modM[xi];
            xi++;
            if(xi <= K)
                *(++p) = xi, *(++q) = i;
            xi3 = xi2, xi2 = xi1, xi1 = xi;
        }
        *(++q) = N+1;
        int *end = p+1;
        int used[105] = {}, d = 0;
        int mndist = 0xfffffff;
        p = &X[1], q = &Y[1], pp = &X[1], qq = &Y[1];
        for(; pp != end;) {
            while(p != end && d < K) {
                if(used[*p] == 0)
                    d++;
                used[*p]++;
                p++, q++;
            }
            if(p == end && d < K)
                break;
            if(mndist > (*(q-1))-(*qq) && d == K)
                mndist = (*(q-1))-(*qq);
            if(used[*pp] == 1)
                d--;
            used[*pp]--, pp++, qq++;
        }
        printf("Case %d: ", ++cases);
        if(mndist != 0xfffffff)
            printf("%d\n", mndist+1);
        else
            puts("sequence nai");
    }
    return 0;
}
