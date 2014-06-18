#include <stdio.h>

int main() {
    int n;
    char s[105];
    while(scanf("%d %s", &n, s) == 2 && n) {
        int flag = 0, i;
        for(i = 0; s[i]; i++) {
            if(s[i]-'0' != n) {
                if(s[i] == '0') {
                    if(flag)
                        putchar(s[i]);
                } else {
                    putchar(s[i]);
                    flag = 1;
                }
            }
        }
        if(!flag)
            putchar('0');
        puts("");
    }
    return 0;
}
