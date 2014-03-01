#include <stdio.h>
#include <string.h>
char str[20], ans[20], len;
void dfs(int idx) {
    if(idx == len) {
        ans[idx] = '\0';
        puts(ans);
        return;
    }
    int i;
    for(i = idx; i >= 1; i--)
        ans[i] = ans[i-1];
    for(i = 0; i <= idx; i++) {
        ans[i] = str[idx];
        dfs(idx+1);
        ans[i] = ans[i+1];
    }
}
int main() {
    int flag = 1;
    while(gets(str)) {
        if(!flag)
            puts("");
        flag = 0;
        len = strlen(str);
        dfs(0);
    }
    return 0;
}
