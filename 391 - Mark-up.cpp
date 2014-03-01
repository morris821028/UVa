#include <stdio.h>
#include <string.h>
int main() {
    char s[1005];
    int i, j;
    int tton = 0;
    while(gets(s)) {
        int len = strlen(s);
        for(i = 0; i < len; i++) {
            if(s[i] == '\\') {
                if(s[i] == '\\' && s[i+1] != '*' && tton == 1)
                    goto L1;
                if(s[i+1] == '\\') {
                    putchar('\\');
                    i++;
                } else if(s[i+1] == 's') {
                    i++, i++;
                    while(s[i] >= '0' && s[i] <= '9')
                        i++;
                    if(s[i] == '.') {
                        i++;
                        while(s[i] >= '0' && s[i] <= '9')
                            i++;
                    }
                    i--;
                } else if(s[i+1] == '*') {
                    i++;
                    if(tton) {
                        tton = 0;
                        continue;
                    }
                    tton = 1;
                    for(j = i+1; s[j]; j++) {
                        if(s[j] == '\\' && s[j+1] == '*') {
                            tton = 0;
                            break;
                        }
                        putchar(s[j]);
                    }
                    i = j+1;
                } else if(s[i+1] == 'b' || s[i+1] == 'i')
                    {i++;}
            } else {
                L1:
                putchar(s[i]);
            }
        }
        puts("");
    }
    return 0;
}
