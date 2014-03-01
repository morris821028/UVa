#include <stdio.h>
char s[20];
int n, m;
void dfs(int i, int m) {
    if(m > i || m < 0)
        return;
    if(!i) {
        s[n] = '\0';
        puts(s);
        return;
    }
    s[n-i] = '0';
    dfs(i-1, m);
    s[n-i] = '1';
    dfs(i-1, m-1);
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        dfs(n, m);
        if(t)
            puts("");
    }
    return 0;
}
