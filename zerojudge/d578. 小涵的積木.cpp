#include <stdio.h>

int main() {
    int n, m, i, j;
    char str[1024];
    while(scanf("%d %d", &n, &m) == 2 && n) {
        getchar();
        n = n*m-1;
        int cnt[1024][128] = {};
        while(n--) {
            gets(str);
            for(i = 0; str[i]; i++)
                cnt[i][str[i]]++;
        }
        for(i = 0; i < 1024; i++)
            for(j = 0; j < 128; j++)
                if(cnt[i][j]%m)
                    putchar(j), j = 129;
        puts("");
    }
    return 0;
}
