#include <stdio.h>
#include <string.h>
char s[50005], buf[50005];
int main() {
    int i, j;
    while(scanf("%s", s) == 1) {
        if(s[0] == '0' && s[0] == '\0')
            break;
        char *p = buf;
        for(i = strlen(s)-1 ; i >= 0; i--) {
            while(i >= 0 && s[i] == '0')
                i--, *p++ = '0';
            j = 0;
            while(i >= 0 && s[i] == '1')
                i--, j++;
            if(j == 1)
                *p++ = '+';
            else {
                *p++ = '-';
                j--;
                while(j--)
                    *p++ = '0';
                *p++ = '+';
            }
        }
        while(p-- != buf)
            putchar(*p);
        puts("");
    }
    return 0;
}
