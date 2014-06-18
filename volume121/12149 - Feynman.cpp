#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        printf("%d\n", n*(n+1)*(2*n+1)/6);
    }
    return 0;
}
