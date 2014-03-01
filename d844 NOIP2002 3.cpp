#include <stdio.h>

int main() {
    char s[50];
    int n, i, j, k;
    while(scanf("%s %d", s, &n) == 2) {
        int ch[10][10] = {}, x, y;
        while(n--) {
            scanf("%d %d", &x, &y);
            ch[x][y] = 1;
        }
        for(k = 0; k < 10; k++)
            for(i = 0; i < 10; i++)
                for(j = 0; j < 10; j++)
                    ch[i][j] = ch[i][j] or (ch[i][k] and ch[k][j]);
        int cnt[10] = {};
        for(i = 0; i < 10; i++) {
            for(j = 0; j < 10; j++) {
                if(i != j)
                cnt[i] += ch[i][j];
            }
        }
        long long res[100] = {};
        res[0] = 1;
        for(i = 0; s[i]; i++) {
         //   res *= (cnt[s[i]-'0']+1);
            for(j = 0; j < 99; j++)
                res[j] *= cnt[s[i]-'0']+1;
            for(j = 0; j < 99; j++) {
                if(res[j] >= 10)
                    res[j+1] += res[j]/10, res[j] %= 10;
            }
        }
        i = 99;
        while(res[i] == 0)  i--;
        while(i >= 0)   printf("%d", res[i--]);
        puts("");
    }
    return 0;
}
