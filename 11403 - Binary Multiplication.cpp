#include <stdio.h>
#include <string.h>

int main() {
    char a[105], b[105];
    int first = 0;
    while(scanf("%s %s", a, b) == 2) {
        if(!strcmp("0", a) && !strcmp("0", b))
            break;
        int la = strlen(a), lb = strlen(b);
        int ans[105][105] = {};
        int i, j, ia, ja;
        for(i = lb-1, ia = 0; i >= 0; i--, ia++) {
            for(j = la-1, ja = 0; j >= 0; j--, ja++) {
                ans[ia][ia+ja] += (b[i]-'0')*(a[j]-'0');
                ans[lb][ia+ja] += ans[ia][ia+ja];
            }
            for(j = 0; j < 100; j++) {
                ans[i][j+1] += ans[i][j]/2;
                ans[i][j] %= 2;
            }
            for(j = 0; j < 100; j++) {
                ans[lb][j+1] += ans[lb][j]/2;
                ans[lb][j] %= 2;
            }
        }
        int mx = la > lb ? la : lb;
        int anslen;
        for(i = 99; i >= 0; i--)
            if(ans[lb][i])  break;
        if(i < 0)   i = 0;
        anslen = i+1;
        if(i+1 > mx)    mx = i+1;
        for(i = 0; i < mx-la; i++)
            putchar(' ');
        puts(a);
        for(i = 0; i < mx-lb; i++)
            putchar(' ');
        puts(b);
        int mx2 = la > lb ? la : lb;
        for(i = 0; i < mx-mx2; i++)
            putchar(' ');
        for(i = 0; i < mx2; i++)
            putchar('-');
        puts("");
        for(i = 0; i < lb; i++, puts("")) {
            for(j = 0; j < mx-i-la; j++)
                putchar(' ');
            for(j = i+la-1; j >= i; j--)
                putchar(ans[i][j]+'0');
        }
        for(i = 0; i < mx; i++)
            putchar('-');
        puts("");
        for(i = 0; i < mx-anslen; i++)
            putchar(' ');
        for(i = anslen-1; i >= 0; i--)
            putchar(ans[lb][i]+'0');
        puts("");
        puts("");
    }
    return 0;
}
/*
11 11
111 10
10 111
0 0
*/
