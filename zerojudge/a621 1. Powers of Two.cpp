#include <stdio.h>

int main() {
    int n, i;
    scanf("%d", &n);
    for(i = 0; i <= n; i++)
        printf("2^%d = %d\n", i, 1<<i);
    return 0;
}
