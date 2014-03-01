#include <stdio.h>

int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        if(n&1) puts("-1");
        else {
            for(i = 1; i < n; i += 2) {
                if(i != 1)  putchar(' ');
                printf("%d %d", i+1, i);
            }
            puts("");
        }
    }
    return 0;
}
