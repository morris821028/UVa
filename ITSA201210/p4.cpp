#include <stdio.h>
int A[100], i, n;
int ans;
void dfs(int dep) {
    if(dep >= ans)
        return;
    int flag = 0, i, tmp, j;
    for(i = 0; i < n; i++) {
        if(A[i] != i) {
            j = A[i];
            tmp = A[i], A[i] = A[j], A[j] = tmp;
            dfs(dep+1);
            flag = 1;
            tmp = A[i], A[i] = A[j], A[j] = tmp;
        }
    }
    if(flag == 0) {
        if(ans > dep)
            ans = dep;
    }
}
int main() {
    while(scanf("%d", &n) == 1) {
        ans = n*n;
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
        }
        dfs(0);
        printf("%d\n", ans);
    }
    return 0;
}
