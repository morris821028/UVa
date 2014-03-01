#include <stdio.h>
#include <vector>
using namespace std;
struct Arc {
    int to;
};
int n, A[90000], B[90000];
int main() {
    int i;

    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        vector<Arc> mylink[90000];
        Arc tmp;
        for(i = 1; i < n; i++) {
            scanf("%d", &B[i]);
            tmp.to = i;
            mylink[B[i]].push_back(tmp);
        }
        int dp[90000][2] = {};
        for(i = n-1; i >= 0; i--) {
            int sum1 = 0, sum2 = 0;
            for(vector<Arc>::iterator j = mylink[i].begin(); j != mylink[i].end(); j++) {
                sum1 += dp[j->to][0] > dp[j->to][1] ? dp[j->to][0] : dp[j->to][1];
                sum2 += dp[j->to][1];
            }
            dp[i][0] = sum2+A[i];
            dp[i][1] = sum1;
        }
        int ans = dp[0][0] > dp[0][1] ? dp[0][0] : dp[0][1];
        printf("%d\n", ans);
    }
    return 0;
}
