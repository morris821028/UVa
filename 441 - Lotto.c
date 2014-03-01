#include <stdio.h>
int n, A[13], ans[6];
void dfs(int idx, int i) {
    if(idx == 6) {
        printf("%d", ans[0]);
        for(i = 1; i < 6; i++)
            printf(" %d", ans[i]);
        puts("");
        return;
    }
    for(; i < n; i++)
        ans[idx] = A[i], dfs(idx+1, i+1);
}
int main() {
    int first = 1, i;
    while(scanf("%d", &n) == 1 && n) {
        if(!first)
            puts("");
        first = 0;
        for(i = 0; i < n; i++)
            scanf("%d", A+i);
        dfs(0, 0);
    }
    return 0;
}
