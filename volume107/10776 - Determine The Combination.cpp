#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int ch[50], ch_num[50];
char ans[50];
void dfs(int n, int m, int i, int idx) {
    if(n == 0) {
        ans[idx] = '\0';
        puts(ans);
        return;
    }
    for(; i <= m; i++) {
        if(ch_num[i]) {
            ch_num[i]--;
            ans[idx] = ch[i];
            dfs(n-1, m, i, idx+1);
            ch_num[i]++;
        }
    }
}
int main() {
    char s[30];
    int n, m, i, j;
    while(scanf("%s %d", s, &n) == 2) {
        m = strlen(s);
        sort(s, s+m);
        ch[0] = s[0], ch_num[0] = 1;
        for(i = 1, j = 0; i < m; i++) {
            if(s[i] != s[i-1]) {
                j++;
                ch[j] = s[i];
                ch_num[j] = 1;
            } else
                ch_num[j]++;
        }
        m = j;
        dfs(n, m, 0, 0);
    }
    return 0;
}
