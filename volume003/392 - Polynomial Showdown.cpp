#include <stdio.h>
#include <stdlib.h>

int main() {
    int p[9], i, j;
    while(scanf("%d", &p[8]) == 1) {
        for(i = 7; i >= 0; i--)
            scanf("%d", &p[i]);
        j = 8;
        while(!p[j] && j >= 0)    j--;
        int flag = 0;
        if(j == -1)
            putchar('0');
        for(i = j; i >= 0; i--) {
            if(p[i]) {
                if(flag) {
                    putchar(' ');
                    if(p[i] > 0)
                        putchar('+');
                    else
                        putchar('-');
                    putchar(' ');
                } else {
                    if(p[i] < 0)
                        putchar('-');
                    flag = 1;
                }
                if(i) {
                    if(abs(p[i]) != 1)
                        printf("%d", abs(p[i]));
                    putchar('x');
                    if(i != 1)
                        printf("^%d", i);
                }
                else {
                    printf("%d", abs(p[i]));
                }
            }
        }
        puts("");
    }
    return 0;
}
