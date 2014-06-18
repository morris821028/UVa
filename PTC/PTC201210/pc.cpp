#include <stdio.h>
int used[105] = {}, len;
int flag, m, n, w[105] = {};
void dfs(int idx, int now, int st, int sum) {
    if(flag)    return;
    if(sum > len)   return;
    if(sum == len) {
        dfs(0, now+1, 0, 0);
        return;
    }
    if(now == m) {
        flag = 1;
        return;
    }
    int i;
    if(st == 0) {
        for(i = 0; i < n; i++) {
            if(used[i] == 0) {
                used[i] = 1;
                dfs(i+1, now, 1, w[i]);
                used[i] = 0;
                break;
            }
        }
    } else {
        for(i = idx; i < n; i++) {
            if(used[i] == 0) {
                used[i] = 1;
                dfs(i+1, now, 1, sum+w[i]);
                used[i] = 0;
            }
        }
    }
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &m, &n);
        int sum = 0, i;
        for(i = 0; i < n; i++) {
            scanf("%d", &w[i]);
            sum += w[i];
        }
        if(sum%m) {
            puts("NO");
            continue;
        }
        len = sum/m, flag = 0;
        dfs(0, 0, 0, 0);
        if(flag)
            puts("Congratulations");
        else
            puts("NO");
    }
    return 0;
}
