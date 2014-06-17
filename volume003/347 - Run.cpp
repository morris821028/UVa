#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int used[10] = {};
char s[11] = {};
int ans[100000] = {}, at = 0;
void check(int idx) {
    if(idx == 0)
        return;
    s[idx] = '\0';
    int i, ti, len, cnt = 0;
    char ts[11];
    memcpy(ts, s, sizeof(ts));
    len = strlen(ts);
    for(i = 0; ;) {
        if(ts[i] == -1) {
            if(cnt == len && i == 0) {
                int n;
                sscanf(s, "%d", &n);
                ans[at++] = n;
                return;
            }
            return;
        }
        cnt++;
        ti = i + ts[i]-'0';
        ts[i] = -1;
        i = ti;
        if(i >= len)
            i %= len;
    }
}
void dfs(int idx) {
    check(idx);
    int i;
    for(i = 1; i <= 9; i++) {
        if(used[i] == 0) {
            s[idx] = i+'0';
            used[i] = 1;
            dfs(idx+1);
            used[i] = 0;
        }
    }
}
int main() {
    int n, test = 0, tmp, i;
    dfs(0);
    sort(ans, ans+at);
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < at; i++)
            if(ans[i] >= n) {
                tmp = ans[i];
                break;
            }
        printf("Case %d: %d\n", ++test, tmp);
    }
    return 0;
}
