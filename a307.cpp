#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    while(scanf("%s", s) == 1) {
        if(s[0] == '-')
            putchar('-');
        int len = strlen(s)-1;
        while(len >= 0 && s[len] == '0')
            len--;
        if(len < 0 || s[len] == '-') {
            puts("0");
            continue;
        }
        while(len >= 0 && s[len] != '-')
            putchar(s[len]), len--;
        puts("");
    }
    return 0;
}
