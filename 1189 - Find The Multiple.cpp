#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int C[205] = {}, t = 1%n, i, j;
        for(i = 1; ; i++) {
            if(C[t]) {
                for(j = C[t]; j < i; j++)
                    putchar('1');
                for(j = C[t]-1; j >= 0; j--)
                    putchar('0');
                puts("");
                break;
            }
            C[t] = i;
            t = (t*10+1)%n;
        }
    }
    return 0;
}
