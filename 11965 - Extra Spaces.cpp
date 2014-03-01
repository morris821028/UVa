#include <stdio.h>
#include <iostream>
using namespace std;
int main() {
    scanf("%*d");
    int cases = 0, n, i;
    char s[1024];
    while(scanf("%d", &n) == 1) {
        cin.ignore(100, '\n');
        if(cases)   puts("");
        printf("Case %d:\n", ++cases);
        while(n--) {
            gets(s);
            for(i = 0; s[i]; i++) {
                if(s[i] == ' ') {
                    while(s[i] && s[i] == ' ')
                        i++;
                    i--;
                    putchar(' ');
                } else
                    putchar(s[i]);
            }
            puts("");
        }
    }
    return 0;
}
