#include <stdio.h>
int main() {
    char s[105];
    int i, j;
    while(1) {
        int person[105][2] = {}, n = 0;
        while(gets(s) && s[0] != '.') {
            for(i = 0; s[i] != ';'; i += 2) {
                if(s[i] == '+')
                    person[n][0] |= 1<<(s[i+1]-'A');
                else
                    person[n][1] |= 1<<(s[i+1]-'A');
            }
            n++;
        }
        if(n == 0)  break;
        int m = 1<<16;
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++) {
                if(i&person[j][0])  continue;
                if((m-1-i)&person[j][1])  continue;
                break;
            }
            if(j == n) {
                printf("Toppings: ");
                for(j = 0; j < 16; j++)
                    if((i>>j)&1)
                        putchar(j+'A');
                puts("");
                break;
            }
        }
        if(i == m)
            puts("No pizza can satisfy these requests.");
    }
    return 0;
}
