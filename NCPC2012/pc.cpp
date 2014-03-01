#include <cstdio>
#include <algorithm>
using namespace std;
int M[2505][35], IM[2505];
int n, m;
bool cmp(int a, int b) {
    static int i;
    for(i = 0; i < m; i++)
        if(M[a][i] != M[b][i])
            return M[a][i] < M[b][i];
    return true;
}
bool cmp2(int a, int b) {
    static int i;
    for(i = 0; i < m; i++)
        if(M[a][i] >= M[b][i])
            return false;
    return true;
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++)
                scanf("%d", &M[i][j]);
            sort(M[i], M[i]+m);
            IM[i] = i;
        }
        sort(IM, IM+n, cmp);
        int dp[2505] = {}, ans = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < i; j++) {
                if(cmp2(IM[j], IM[i])) {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            ans = max(dp[i], ans);
        }
        printf("%d\n", ans+1);
    }
    return 0;
}
/*
3
2 3
6 3 5
1 4 2
3 3
1 2 3
1 2 3
4 5 6
3 2
3 1
2 4
6 5
*/
