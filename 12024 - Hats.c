#include <stdio.h>

int main() {
    int N[13] = {0, 0, 1}, P[13] = {1, 1, 2}, n, t;
    for(n = 3; n <= 12; n++) {
        N[n] = N[n-1]*n + (n%2 == 0 ? 1 : -1);
        P[n] = P[n-1]*n;
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        printf("%d/%d\n", N[n], P[n]);
    }
    return 0;
}
