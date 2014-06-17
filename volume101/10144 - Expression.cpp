#include <stdio.h>
char s[105][5005];
int main() {
    sprintf(s[0], "((A0|B0)|(A0|B0))");
    int i, t;
    for(i = 1; i <= 100; i++) {
        sprintf(s[i], "((A%d|B%d)|(%s|((A%d|A%d)|(B%d|B%d))))", i, i, s[i-1], i, i, i, i);
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &i);
        puts(s[i-1]);
        if(t)   puts("");
    }
    return 0;
}
