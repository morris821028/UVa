#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
using namespace std;
#define MAXW (2100 + 10)
#define INF 0x3f3f3f3f
int dp[2][MAXW][MAXW]; // [previous i books][2-layer width][3-layer width]
int used[2][MAXW][MAXW], usedcase = 0;

void update(int q, int j, int k, int val) {
    if (used[q][j][k] != usedcase) {
        used[q][j][k] = usedcase;
        dp[q][j][k] = INF;
    }
    dp[q][j][k] = min(dp[q][j][k], val);
}
int main() {
    int testcase, N, H, W;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        vector< pair<int, int> > D;
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &H, &W);
            D.push_back(make_pair(H, W));
        }
        sort(D.begin(), D.end(), greater< pair<int, int> >());
        
        int p = 0, q = 1, sum = D[0].second;
        usedcase++;
        dp[0][0][0] = 0, used[0][0][0] = usedcase;
        for (int i = 1; i < D.size(); i++) {
            usedcase++;
            for (int j = 0; j <= sum; j++) {
                for (int k = 0; j+k <= sum; k++) {
                    if (used[p][j][k] != usedcase - 1)  continue;
                    // place 1-layer
                    update(q, j, k, dp[p][j][k]);
                    // place 2-layer
                    update(q, j+D[i].second, k, dp[p][j][k] + (j == 0 ? D[i].first : 0));
                    // place 3-layer
                    if (j > 0)
                    update(q, j, k+D[i].second, dp[p][j][k] + (k == 0 ? D[i].first : 0));
                }
            }
            sum += D[i].second;
            p = 1 - p, q = 1 - q;
        }
        int ret = INF;
        for (int i = 1; i <= sum; i++) {
            for (int j = 1; i+j <= sum; j++) {
                if (used[p][i][j] != usedcase)  continue;
                int W = 0, H = 0;
                W = max(sum - i - j, max(i, j));
                H = dp[p][i][j] + D[0].first;
//                printf("%d %d %d, %d %d %d = %d\n", i, j, sum - i - j, W, H, dp[p][i][j], W * H);
                ret = min(ret, W * H);
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*

*/