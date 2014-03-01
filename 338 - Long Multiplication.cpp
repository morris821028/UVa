#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int main() {
    char x[20], y[20];
    int i, j;
    while(scanf("%s %s", x, y) == 2) {
        int lx = strlen(x), ly = strlen(y), ol = ly;
        int g[30][30] = {}, a, b;
        for(i = ly-1, a = 0; i >= 0; i--, a++) {
            for(j = lx-1, b = 0; j >= 0; j--, b++) {
                g[a][a+b] += (y[i]-'0')*(x[j]-'0');
            }
        }
        for(i = 0; i <= ly; i++) {
            for(j = 0; j < 30; j++) {
                if(g[i][j] >= 10) {
                    g[i][j+1] += g[i][j]/10;
                    g[i][j] %= 10;
                }
                if(i != ly) {
                    g[ly][j] += g[i][j];
                }
            }
        }
        for(i = 0; i < 30; i++)
            if(g[ly-1][i] != g[ly][i])
                break;
        if(i == 30) ol--;
        int len = 29;
        while(len >= 0 && g[ly][len] == 0)  len--;
        if(len < 0)
            len = max(lx, ly);
        else
            len++;
        for(i = 0; i < len-lx; i++)
            putchar(' ');
        puts(x);
        for(i = 0; i < len-ly; i++)
            putchar(' ');
        puts(y);
        for(i = 0; i < len-max(lx, ly); i++)
            putchar(' ');
        for(i = 0; i < max(lx, ly); i++)
            putchar('-');
        puts("");
        int hasVal = 0;
        for(i = 0; i < ol; i++) {
            int flag = 0;
            for(j = len-1; j >= i; j--) {
                if(g[i][j]) flag = 1;
                if(flag) {
                    flag = len-1;
                    while(flag > j)
                        putchar(' '), flag--;
                    while(j >= i)
                        printf("%d", g[i][j]), j--;
                    break;
                }
            }
            if(flag)
                puts(""), hasVal++;
        }
        if(hasVal) {
            for(i = len-1; i >= 0; i--)
                putchar('-');
            puts("");
        }
        i = len-1;
        while(i >= 0 && g[ol][i] == 0)
            i--;
        if(i < 0) i++;
        len--;
        while(len > i)
            putchar(' '), len--;
        while(i >= 0)
            printf("%d", g[ol][i]), i--;
        puts("\n");
    }
    return 0;
}
