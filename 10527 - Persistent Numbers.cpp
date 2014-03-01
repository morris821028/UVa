#include <stdio.h>
#include <stdlib.h>
int main() {
    char s[3005];
    int i, j;
    while(gets(s)) {
        if(s[0] == '-') break;
        if(s[1] == '\0') {
            printf("1%s\n", s);
            continue;
        }
        for(i = 0; s[i]; i++)   s[i] -= '0';
        int len = i, idx = 0, st = 0;
        char stk[3005];
        for(i = 9; i >= 2; i--) {
            while(1) {
                int mod = 0;
                for(j = st; j < len; j++) {
                    mod = mod*10 + s[j];
                    mod %= i;
                }
                if(!mod) {
                    stk[idx++] = i+'0';
                    mod = 0;
                    for(j = st; j < len; j++) {
                        mod = mod*10 + s[j];
                        s[j] = mod/i;
                        mod %= i;
                    }
                    while(s[st] == 0)   st++;
                } else  break;
            }
        }
        if(st == len-1 && s[st] == 1) {
            for(i = idx-1; i >= 0; i--)
                putchar(stk[i]);
            puts("");
        } else
            puts("There is no such number.");
    }
    return 0;
}
