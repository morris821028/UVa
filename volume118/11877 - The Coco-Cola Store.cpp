#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n)
        printf("%d\n", n/2);
    return 0;
}
