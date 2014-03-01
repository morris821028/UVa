#include <stdio.h>
int A[10], ans, cnt;
int dfs(int n, int l) {
    int flag = 0, i, t;
    for(i = 1; i < n; i++) {
        if(A[i] < A[i-1]) {
            t = A[i], A[i] = A[i-1], A[i-1] = t;
            dfs(n, l+1);
            t = A[i], A[i] = A[i-1], A[i-1] = t;
            flag = 1;
        }
    }
    if(flag == 0) {
        if(ans > l)
            ans = l, cnt = 0;
        if(ans == l)
            cnt++;
    }
}
int main() {
    int n, cases = 0, i;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        ans = 0xffffff, cnt = 0;
        dfs(n, 0);
        if(ans == 0)    cnt = 0;
        printf("There are %d swap maps for input data set %d.\n", cnt, ++cases);
    }
    return 0;
}
