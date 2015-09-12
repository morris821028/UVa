#include <stdio.h>
#include <limits.h>
#include <algorithm>
using namespace std;
// IDA*
int n, m;
long long ret;
void dfs(int idx, long long V, long long S, int limR, int limH) {
    if (V + (long long) limR*limR*limH*(m - idx) < n || V > n)
        return ;
    if ((limR && S + 2*(n - V)/limR > ret) || S > ret)
        return ;
    if (idx == m) {
        if (V == n)
            ret = min(ret, S);
        return ;
    }
    for (int i = m - idx; i <= limR; i++)
        for (int j = m - idx; j <= limH; j++)
            dfs(idx+1, V + i*i*j, S + 2*i*j, i-1, j-1);
}
int main() {
    while (scanf("%d %d", &n, &m) == 2) {
        ret = INT_MAX;
        for (int i = m; i*i*m <= n; i++) {
            for (int j = m; i*i*j <= n; j++) {
                dfs(1, i*i*j, 2*i*j + i*i, i-1, j-1);
            }
        }
        if (ret == INT_MAX) ret = 0;
        printf("%lld\n", ret);
    }
    return 0;
}
