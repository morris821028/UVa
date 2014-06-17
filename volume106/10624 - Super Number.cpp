#include <stdio.h>
int find, n, m;
int N[50];
int div(int len, int j) {
    static int i, tmp;
    for(i = 1, tmp = 0; i < len; i++) {
        tmp = tmp*10 + N[i];
        tmp %= len;
    }
    tmp = tmp*10 + j;
    return tmp%len;
}
void dfs(int idx) {
    if(find)    return;
    int i, j = 1;
    if(idx == m+1) {
        find = 1;
        for(i = 1; i <= m; i++)
            printf("%d", N[i]);
        return;
    }
    for(i = (idx == 1); i < 10; i += j) {
        if(idx >= n && div(idx, i) == 0) {
            N[idx] = i;
            j = idx;
            dfs(idx+1);
        } else if(idx < n) {
            N[idx] = i;
            dfs(idx+1);
        }
    }
}
int main() {
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        printf("Case %d: ", ++cases);
        find = 0;
        dfs(1);
        if(!find)   puts("-1");
        else    puts("");
    }
    return 0;
}

