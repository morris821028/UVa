#include <stdio.h>
#include <stdlib.h>

int main() {
    char s[1000], ch;
    int n, i;
    while(gets(s)) {
        scanf("%d", &n);
        while(ch = getchar()) {
            if(ch == '\n')
                break;
        }
        for(i = 0; s[i]; i++) {
            if(s[i] >= 'a' && s[i] <= 'z')
                printf("%c", (s[i]-'a'+n)%26+'a');
            else if(s[i] >= 'A' && s[i] <= 'Z')
                printf("%c", (s[i]-'A'+n)%26+'A');
            else if(s[i] >= '0' && s[i] <= '9')
                printf("%c", (s[i]-'0'+n)%10+'0');
            else
                printf("%c", s[i]);
        }
        puts("");
    }
    return 0;
}
