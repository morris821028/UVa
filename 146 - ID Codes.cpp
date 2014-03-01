#include <stdio.h>
#include <string.h>
int cnt[26], flag, len;
char str[100], tmp[100];
void dfs(int idx) {
    if(flag == 2)
        return ;
    if(idx == len) {
        if(flag == 0) {
            flag = 1;
        } else {
            tmp[idx] = '\0';
            puts(tmp);
            flag = 2;
        }
        return ;
    }
    int i;
    for(i = 0; i < 26; i++) {
        if(flag == 0) {
            if(str[idx]-'a' == i) {
                cnt[i]--;
                tmp[idx] = i+'a';
                dfs(idx+1);
                cnt[i]++;
            }
        } else {
            if(cnt[i] > 0) {
                cnt[i]--;
                tmp[idx] = i+'a';
                dfs(idx+1);
                cnt[i]++;
            }
        }
    }
}
int main() {
    int i;
    while(scanf("%s", str) == 1) {
        if(!strcmp("#", str))
            break;
        memset(cnt, 0, sizeof(cnt));
        flag = 0, len = strlen(str);
        for(i = 0; str[i]; i++)
            cnt[str[i]-'a']++;
        dfs(0);
        if(flag != 2)
            puts("No Successor");
    }
    return 0;
}
