#include <stdio.h>
#include <stdlib.h>
int main() {
    char s[10];
    gets(s);
    int L, R;
    while(gets(s)) {
        L = (s[0]-'A')*26*26+(s[1]-'A')*26+(s[2]-'A');
        R = (s[4]-'0')*1000+(s[5]-'0')*100+(s[6]-'0')*10+(s[7]-'0');
        if(abs(L-R) <= 100)
            puts("nice");
        else
            puts("not nice");
    }
    return 0;
}
