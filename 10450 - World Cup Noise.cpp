#include <stdio.h>

int main() {
    int t, cases = 0, n;
    long long f[60] = {1,2};
    for(t = 2; t < 60; t++) f[t] = f[t-1]+f[t-2];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        printf("Scenario #%d:\n%lld\n\n", ++cases, f[n]);
    }
    return 0;
}
