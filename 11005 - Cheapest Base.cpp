#include <stdio.h>
#include <stdlib.h>
#define oo 2147483647
int W[36];
int Sum, Min = oo;
int C(int n, int m, int now) {
    if(now == 0 && n == 0) {
        Sum += W[0];
        return 0;
    }
    if(n == 0)  return 0;
    C(n/m, m, now+1);
    Sum += W[n%m];
}
int main() {
    int T, Case = 0, i, n, x;
    scanf("%d", &T);
    while(T--) {
        if(Case > 0)
            puts("");
        printf("Case %d:\n", ++Case);
        for(i = 0; i < 36; i++)
            scanf("%d", &W[i]);
        scanf("%d", &n);
        while(n--) {
            scanf("%d", &x);
            Min = oo;
            for(i = 2; i <= 36; i++) {
                Sum = 0;
                C(x, i, 0);
                if(Min > Sum)
                    Min = Sum;
            }
            printf("Cheapest base(s) for number %d:", x);
            for(i = 2; i <= 36; i++) {
                Sum = 0;
                C(x, i, 0);
                if(Sum == Min)
                    printf(" %d", i);
            }
            puts("");
        }
    }
    return 0;
}
