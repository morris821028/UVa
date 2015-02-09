#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define MAXM 2505
#define MAXN 55
int dp[MAXM][MAXN], plateSize[MAXM]; // [previous i-th size plate][tail plate from stack]
int has[MAXM][MAXN];
int main() {
    int N, M, cases = 0;
    int h, x;
    while (scanf("%d", &N) == 1) {
        vector< pair<int, int> > D;
        for (int i = 0; i < N; i++) {
            scanf("%d", &h);
            for (int j = 0; j < h; j++) {
                scanf("%d", &x);
                D.push_back(make_pair(x, i));
            }
        }
        
        memset(has, 0, sizeof(has));
        memset(dp, 63, sizeof(dp));
        
        sort(D.begin(), D.end());
        D.resize(unique(D.begin(), D.end()) - D.begin()); // remove same size
        M = 0;
        for (int i = 0; i < D.size(); ) {
            int cnt = 0, j = i;
            while (j < D.size() && D[i].first == D[j].first) {
                has[M][D[j].second] = 1;
                j++, cnt++;
            }
            plateSize[M] = cnt;
            M++, i = j;
        }
        for (int i = 0; i < N; i++) {
            if (has[0][i])
                dp[0][i] = plateSize[0];
        }
        for (int i = 1; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (!has[i][j])
                    continue;
                for (int k = 0; k < N; k++) {
                    if (has[i][k] && (j != k || plateSize[i] == 1)) // merge tail ...k-k..j
                        dp[i][j] = min(dp[i][j], dp[i-1][k] + plateSize[i] - 1);
                    else
                        dp[i][j] = min(dp[i][j], dp[i-1][k] + plateSize[i]);
                }
            }
        }
        int ret = 0x3f3f3f3f;
        for (int i = 0; i < N; i++) {
            ret = min(ret, dp[M-1][i]);
        }
        printf("Case %d: %d\n", ++cases, ret * 2 - N - 1);
    }
    return 0;
}
/*
 2
 3 1 2 4
 2 3 5
 3
 4 1 1 1 1
 4 1 1 1 1
 4 1 1 1 1
 2
 3 1 2 4
 3 1 3 4
*/