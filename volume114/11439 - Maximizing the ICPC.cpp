#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;
int g[105][105], gt[105];
int mx[105], my[105], used[105];
int dfs(int now) {
    printf("%d\n", now);
    int i, x;
    for(i = 0; i < gt[now]; i++) {
        x = g[now][i];
        if(!used[x]) {
            used[x] = 1;
            if(my[x] == 0 || dfs(my[x])) {
                mx[now] = x, my[x] = now;
                return 1;
            }
        }
    }
    return 0;
}
int check(int n) {
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    int matched = 0, i;
    for(i = 1; i <= n; i++) {
        if(!mx[i]) {
            printf("xx");
            memset(used, 0, sizeof(used));
            if(dfs(i))
                matched++;
        }
    }
    return matched;
}
int main() {
    int testcase;
    int A[100][100], C[10000];
    int n, m, i, j, k;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        m = 1<<n;
        set<int> B;
        for(i = 1; i <= m; i++) {
            for(j = i+1; j <= m; j++) {
                scanf("%d", &A[i][j]);
                B.insert(A[i][j]);
            }
        }
        n = 0;
        for(set<int>::iterator it = B.begin();
            it != B.end(); it++) {
            C[n++] = *it;
        }
        int l = 0, r = n-1, mid, ok = 0;
        while(l <= r) {
            mid = (l+r)/2;
            memset(gt, 0, sizeof(gt));
            printf("C[] = %d\n", C[mid]);
            for(i = 1; i <= m; i++)
                for(j = i+1; j <= m; j++)
                    if(A[i][j] >= C[mid])
                        g[i][gt[i]++] = m+j;
            if(check(m) == m)
                l = mid+1, ok = mid;
            else
                r = mid-1;
        }
        printf("%d\n", C[ok]);
    }
    return 0;
}
