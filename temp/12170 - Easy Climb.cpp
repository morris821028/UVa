#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define MAXN 128
#define INF (1LL<<60)
long long dp[MAXN][MAXN*MAXN];
long long llabs(long long x) {
    return x < 0 ? -x : x;
}
int main() {
    int testcase, N;
    long long D, h[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %lld", &N, &D);
        for (int i = 0; i < N; i++)
            scanf("%lld", &h[i]);
        
        vector<long long> A;
        map<long long, int> R;
        for (int i = 0; i < N; i++) {
            for (int j = -N; j <= N; j++) {
                A.push_back(h[i] + D * j);
            }
        }
        sort(A.begin(), A.end());
        A.resize(unique(A.begin(), A.end()) - A.begin());
        for (int i = 0; i < A.size(); i++)
            R[A[i]] = i;
        for (int i = 0; i < A.size(); i++) {
            dp[0][i] = INF;
        }
        dp[0][R[h[0]]] = 0;
        for (int i = 1; i < N; i++) {
            deque< pair<long long, long long> > Q;
            for (int j = 0, k = 0; j < A.size(); j++) {
                while (k < A.size() && A[k] <= A[j] + D) {
                    long long x = A[k];
                    long long y = dp[i-1][k];
                    while (!Q.empty() && Q.back().second >= y)
                        Q.pop_back();
                    if (y != INF)
                        Q.push_back(make_pair(x, y));
                    k++;
                }
                while (!Q.empty() && Q.front().first < A[j] - D)
                    Q.pop_front();
                if (Q.empty())
                    dp[i][j] = INF;
                else
                    dp[i][j] = llabs(h[i] - A[j]) + Q.front().second;
            }
        }
        
        long long ret = dp[N-1][R[h[N-1]]];
        if (ret == INF) {
            puts("impossible");
        } else {
            printf("%lld\n", dp[N-1][R[h[N-1]]]);
        }
    }
    return 0;
}
/*

*/