#include <cstdio>
#include <set>
using namespace std;

int main() {
    int n, m, cases = 0, i, j;
    int x, y;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n < 0 && m < 0)  break;
        set<int> r[101];
        int used[101] = {}, ut = -1;
        int dp[101][101][2] = {};
        int cnt = 0;
        while(scanf("%d %d", &x, &y) == 2) {
            if(!x && !y)    break;
            r[x].insert(y);
            used[x] = 1;
        }
        printf("CASE#%d: ", ++cases);
        for(i = 1; i <= n; i++)
            if(used[i]) used[++ut] = i;
        i = used[0];
        cnt = 1;
        for(set<int>::iterator it = r[i].begin();
            it != r[i].end(); it++, cnt++) {
            dp[i][*it][0] = cnt;/*items*/
            dp[i][*it][1] = 1;/*way cnt*/
        }
        int st, ed;
        for(st = 1; st <= ut; st++) {
            i = used[st];
            for(set<int>::iterator it = r[i].begin();
                it != r[i].end(); it++) {
                for(ed = st; ed >= 0; ed--) {
                    j = used[ed];
                    for(set<int>::iterator jt = r[j].begin();
                        jt != r[j].end(); jt++) {
                        if(*jt > *it)   break;
                        if(i == j && *it == *jt)    break;
                        if(dp[i][*it][0] < dp[j][*jt][0]+1)
                            dp[i][*it][0] = dp[j][*jt][0]+1, dp[i][*it][1] = 0;
                        if(dp[i][*it][0] == dp[j][*jt][0]+1)
                            dp[i][*it][1] += dp[j][*jt][1];
                    }
                }
                if(!dp[i][*it][0])
                    dp[i][*it][0] = 1, dp[i][*it][1] = 1;
            }
        }
        int ans = 0, way = 0;
        for(st = 0; st <= ut; st++) {
            i = used[st];
            for(set<int>::iterator it = r[i].begin();
                it != r[i].end(); it++) {
                if(dp[i][*it][0] > ans)
                    ans = dp[i][*it][0], way = 0;
                if(dp[i][*it][0] == ans)
                    way += dp[i][*it][1];
            }
        }
        printf("%d %d\n", ans, way);
    }
    return 0;
}
