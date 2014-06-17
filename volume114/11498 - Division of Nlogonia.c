#include <stdio.h>

int main() {
    int n, x, y, a, b;
    while(scanf("%d", &n) == 1 && n) {
        scanf("%d %d", &x, &y);
        while(n--) {
            scanf("%d %d", &a, &b);
            if(a == x || b == y)
                puts("divisa");
            else if(a > x && b > y)
                puts("NE");
            else if(a < x && b > y)
                puts("NO");
            else if(a < x && b < y)
                puts("SO");
            else
                puts("SE");
        }
    }
    return 0;
}
