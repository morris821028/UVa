#include <stdio.h>
char s[20], buf[20];
int t, n, m, ans;
void dfs(int idx, int k) {
    if(k > m)   return;
    if(idx == n) {
        ans++;
        return;
    }
    buf[idx] = 'A';
    dfs(idx+1, k+(buf[idx] != s[idx]));
    buf[idx] = 'C';
    dfs(idx+1, k+(buf[idx] != s[idx]));
    buf[idx] = 'G';
    dfs(idx+1, k+(buf[idx] != s[idx]));
    buf[idx] = 'T';
    dfs(idx+1, k+(buf[idx] != s[idx]));
}
void dfs2(int idx, int k) {
    if(k > m)   return;
    if(idx == n) {
        buf[idx] = '\0';
        puts(buf);
        return;
    }
    buf[idx] = 'A';
    dfs2(idx+1, k+(buf[idx] != s[idx]));
    buf[idx] = 'C';
    dfs2(idx+1, k+(buf[idx] != s[idx]));
    buf[idx] = 'G';
    dfs2(idx+1, k+(buf[idx] != s[idx]));
    buf[idx] = 'T';
    dfs2(idx+1, k+(buf[idx] != s[idx]));
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        scanf("%s", s);
        ans = 0;
        dfs(0, 0);
        printf("%d\n", ans);
        dfs2(0, 0);
    }
    return 0;
}
