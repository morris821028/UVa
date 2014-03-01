#include <stdio.h>

int main() {
    char s[1000][26] = {}, x[20];
    int n = 0, i, j, ans;
    while(scanf("%s", x) == 1) {
        if(x[0] == '#') break;
        for(i = 0; x[i]; i++)
            s[n][x[i]-'a']++;
        n++;
    }
    gets(x);
    while(gets(x)) {
        if(x[0] == '#') break;
        char t[26] = {};
        ans = 0;
        for(i = 0; x[i]; i++) {
            if(x[i] != ' ')
                t[x[i]-'a']++;
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < 26; j++) {
                if(t[j] < s[i][j])
                    break;
            }
            ans += (j == 26);
        }
        printf("%d\n", ans);
    }
    return 0;
}
