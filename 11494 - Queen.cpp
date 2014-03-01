#include <stdio.h>
#include <stdlib.h>

int main() {
    int x, y, a, b;
    while(scanf("%d %d %d %d", &x, &y, &a, &b) == 4) {
        if(!x && !y && !a && !b)
            break;
        if(x == a && y == b)
            puts("0");
        else if(x == a || y == b || abs(x-a) == abs(y-b))
            puts("1");
        else
            puts("2");
    }
    return 0;
}
