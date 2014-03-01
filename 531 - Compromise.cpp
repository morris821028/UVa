#include <stdio.h>
#include <string.h>

int main() {
    char a[101][31], b[101][31];
    while(1) {
        int la, lb, i, j;
        for(la = 0; ; la++) {
            if(scanf("%s", a[la]) != 1)
                return 0;
            if(!strcmp(a[la], "#"))
                break;
        }
        for(lb = 0; ; lb++) {
            if(scanf("%s", b[lb]) != 1)
                return 0;
            if(!strcmp(b[lb], "#"))
                break;
        }
        int dp[101][101] = {}, from[101][101] = {};
        for(i = 1; i <= la; i++) {
            for(j = 1; j <= lb; j++) {
                if(!strcmp(a[i-1], b[j-1])) {
                    from[i][j] = 3;
                    dp[i][j] = dp[i-1][j-1]+1;
                } else {
                    if(dp[i][j-1] > dp[i-1][j]) {
                        from[i][j] = 1;
                        dp[i][j] = dp[i][j-1];
                    } else {
                        from[i][j] = 2;
                        dp[i][j] = dp[i-1][j];
                    }
                }
            }
        }
        char ans[100], at = 0;
        while(from[la][lb]) {
            switch(from[la][lb]) {
                case 1:lb--;break;
                case 2:la--;break;
                case 3:
                    ans[at++] = la-1;
                    la--, lb--;
            }
        }
        printf("%s", a[ans[at-1]]);
        for(i = at-2; i >= 0; i--)
            printf(" %s", a[ans[i]]);
        puts("");
    }
    return 0;
}
