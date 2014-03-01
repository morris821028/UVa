#include <stdio.h>

int main() {
    long long G;
    int i;
    while(scanf("%lld", &G), G) {
        int first = 0;
        for(i = 9; i >= 0; i--) {
            if((G-i)%9 == 0) {
                if(first)   putchar(' ');
                first = 1;
                printf("%lld", (G-i)/9*10+i);
            }
        }
        puts("");
    }
    return 0;
}
