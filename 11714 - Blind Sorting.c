#include <stdio.h>
#include <math.h>
int main() {
    int n;
    while(scanf("%d", &n) == 1)
        printf("%d\n", n-1 + (int)(log(n-1)/log(2)));
    return 0;
}
