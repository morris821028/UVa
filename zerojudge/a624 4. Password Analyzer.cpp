#include <stdio.h>
#include <string.h>

int main() {
    char s[64];
    while(gets(s)) {
        int l = strlen(s), cnt = 0;
        int i, j;
        if(l >= 8)  cnt++;
        for(i = 0, j = 0; s[i]; i++) {
            if(s[i] >= 'A' && s[i] <= 'Z')
                j |= 1;
            else if(s[i] >= 'a' && s[i] <= 'z')
                j |= 2;
            else
                j |= 4;
        }
        if((j&3) == 3) cnt++;
        if((j&4) != 0 && (j&3)) cnt++;
        printf("This password is %s\n", !cnt ? "WEAK" : cnt < 2 ? "ACCEPTABLE" : cnt < 3 ? "GOOD" : "STRONG");
    }
    return 0;
}
