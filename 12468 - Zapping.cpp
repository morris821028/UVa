#include <stdio.h>
#include <stdlib.h>
#define min(x, y) ((x)<(y)?(x):(y))
int main() {
    int a, b;
    while(scanf("%d %d", &a, &b) == 2) {
        if(a < 0)   break;
        printf("%d\n", min(abs(a-b), min(100-a+b, 100-b+a)));
    }
    return 0;
}
