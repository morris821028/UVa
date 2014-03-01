#include <stdio.h>

int main() {
    int n, i, j;
    while(scanf("%d", &n) == 1) {
        int y = 0;
        for(i = 0; i < 4; i++) {
            y = (y<<8)|((n>>(8*i))&255);
        }
        printf("%d converts to %d\n", n, y);
    }
    return 0;
}
