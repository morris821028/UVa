#include <stdio.h>

int main() {
    int n, cases = 0;
    while(scanf("%d", &n) == 1 && n)
        printf("Case %d: %d\n", ++cases, n/2);
    return 0;
}
