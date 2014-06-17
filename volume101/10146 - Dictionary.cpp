#include <stdio.h>

int main() {
    int t;
    char s[2][100];
    gets(s[0]);
    sscanf(s[0], "%d", &t);
    gets(s[0]);
    while(t--) {
        gets(s[0]);
        puts(s[0]);
        int flag = 1, same = 0, i;
        while(gets(s[flag]) && s[flag][0]) {
            for(i = 0; s[flag][i] && i <= same; i++) {
                if(s[flag][i] != s[1-flag][i])
                    break;
            }
            if(i == same+1)
                same++;
            else
                same = i;
            for(i = 0; i < same; i++)
                putchar(' ');
            puts(s[flag]);
            flag = 1-flag;
        }
        if(t)
            puts("");
    }
    return 0;
}
