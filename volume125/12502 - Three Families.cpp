#include <stdio.h>

int main() {
    int x, y, z;
    scanf("%*d");
    while(scanf("%d %d %d", &x ,&y, &z) == 3)
        printf("%d\n", z*(2*x-y)/(x+y));
    return 0;
}
