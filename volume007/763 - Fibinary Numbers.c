#include <stdio.h>
#include <string.h>

int main() {
    char str[110];
    int first = 0;
    while(scanf("%s", str) == 1) {
        int ans[115] = {}, i, j, len;
        len = strlen(str);
        for(i = len-1, j = 0; i >= 0; i--, j++)
            ans[j] += str[i]-'0';
        scanf("%s", str);
        len = strlen(str);
        for(i = len-1, j = 0; i >= 0; i--, j++)
            ans[j] += str[i]-'0';
        if(first)
            puts("");
        first = 1;
        int AC = 0;
        for(i = 0; i <= 110; i++) {
            if(ans[i] && ans[i+1]) {
                ans[i]--;
                ans[i+1]--;
                ans[i+2]++;
                AC = 1;
            }
            if(ans[i] > 1) {
                ans[i] -= 2;
                if(i == 0)
                    ans[1]++;
                else if(i == 1)
                    ans[2]++, ans[0]++;
                else
                    ans[i+1]++, ans[i-2]++;
                AC = 1;
            }
            if(i == 109 && AC == 1)
                AC = 0, i = -1;
        }
        for(i = 110; i > 0; i--)
            if(ans[i])
                break;
        for(; i >= 0; i--)
            putchar(ans[i]+'0');
        puts("");
    }
    return 0;
}
