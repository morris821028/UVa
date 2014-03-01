#include <stdio.h>
#include <map>
using namespace std;
int ans = 0xffff, n, m;
int A[10005];
map<pair<int, int>, int> R;
void dfs(int l, int r, int sum) {
    if(l > r || sum >= ans) {
        if(sum < ans)
            ans = sum;
        return ;
    }
    int &x = R[make_pair(l, r)];
    if(x == 0 || sum < x) {
        x = sum;
        if(A[l] == A[r])
            dfs(l+1, r-1, sum);
        else {
            dfs(l, r-1, sum+1);
            dfs(l+1, r, sum+1);
        }
    }
}
int main() {
    int t, cases = 0;
    int i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        R.clear();
        ans = m+1;
        dfs(0, n-1, 0);
        printf("Case %d: ", ++cases);
        if(ans == 0) puts("Too easy");
        else if(ans <= m)
            printf("%d\n", ans);
        else
            puts("Too difficult");
    }
    return 0;
}
