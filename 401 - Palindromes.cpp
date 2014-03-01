#include <stdio.h>
#include <string.h>
int main() {
    char s[100];
    while(scanf("%s", s) == 1) {
        int len = strlen(s);
        int i, j;
        char a[] = "A   3  HIL JM O   2TUVWXY5";
        char b[] = "01SE Z  8 ";
        int flag1 = 0, flag2 = 0;
        for(i = 0, j = len-1; i <= j; i++, j--) {
            if(s[i] != s[j])
                flag1 = 1;
            if(s[i] >= 'A' && s[i] <= 'Z') {
                if(s[j] != a[s[i]-'A'])
                    flag2 = 1;
            } else {
                if(s[j] != b[s[i]-'0'])
                    flag2 = 1;
            }
        }
        printf("%s -- is ", s);
        if(flag1) {
            if(flag2)
                puts("not a palindrome.");
            else
                puts("a mirrored string.");
        } else {
            if(flag2)
                puts("a regular palindrome.");
            else
                puts("a mirrored palindrome.");
        }
        puts("");
    }
    return 0;
}
