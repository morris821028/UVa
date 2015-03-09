#include <stdio.h>

int main() {
    int n, m, X[100000], Y[100000], i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        long long ans = 0;
        for(i = 0; i < n; i++)
            scanf("%d", &X[i]);
        for(i = 0; i < n; i++)
            scanf("%d", &Y[i]);
        for(i = 0; i < n; i++)
            for(j = i+1; j < n; j++)
                if((X[i] > X[j] && Y[i] < Y[j]) ||
                   (X[i] < X[j] && Y[i] > Y[j]))
                    ans++, printf("%d %d\n", i, j);
        printf("%lld\n", ans);
    }
    return 0;
}
