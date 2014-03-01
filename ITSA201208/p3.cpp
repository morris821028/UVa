#include <stdio.h>

int main() {
    int n, dd, a, b, x, y;
    while(scanf("%d", &n) == 1) {
        scanf("%d ", &dd);
        scanf("(%d,%d)", &x, &y);
        getchar();
        int flag = 0;
        while(n--) {
            scanf("(%d,%d)", &a, &b);
            getchar();
            if((x-a)*(x-a) + (y-b)*(y-b) <= dd*dd)
                printf("(%d,%d)\n", a, b), flag = 1;
        }
        if(!flag)
            puts("No Answer");
    }
    return 0;
}
/*
3
10
(0,0)
(0,3)
(15,17)
(7,7)
*/
