#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int m, i, j = 1;
        for(m = 1, i = 2, j = 1; ; m += i, i += 2, j++) {
            if(abs(m-n) < j)
                break;
        }
        int x = j, y = j;
        if(j&1) {
            if(n > m)
                x -= (n-m);
            else
                y -= (m-n);
        } else {
            if(n > m)
                y -= (n-m);
            else
                x -= (m-n);
        }
        printf("%d %d\n", x, y);
    }
    return 0;
}
