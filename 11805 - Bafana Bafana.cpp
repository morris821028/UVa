#include <stdio.h>

int main() {
    int t, test = 0, N, K, P;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &N, &K, &P);
        printf("Case %d: %d\n", ++test, (K+P-1)%N+1);
    }
    return 0;
}
