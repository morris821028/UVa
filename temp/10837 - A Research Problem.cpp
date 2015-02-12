#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[5500], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
// phi(n) = m, m = n * (p1 - 1)/p1 * (p2 - 1)/p2 * ...
// pi - 1 | m
vector<int> A;
int ret, used[65536];

void dfs(int m, int n, int idx) {
    if (idx == A.size()) {
        if (m == 1) {
            ret = min(ret, n);
        } else { // pi > sqrt(origin_m)
            int pi = m + 1; // pi - 1 | m
            for (int i = 0; i < Pt && P[i] * P[i] <= pi; i++) {
                if (pi%P[i] == 0)
                    return ;
            }
            for (int i = 0; i < A.size(); i++) {
                if (used[i] && pi == A[i])
                    return ;
            }
            ret = min(ret, n * pi);
        }
        return ;
    }
    dfs(m, n, idx+1);
    if (m%(A[idx]-1) == 0) {
        m /= A[idx]-1;
        n *= A[idx];
        used[idx] = 1;
        while (true) {
            dfs(m, n, idx+1);
            if (m%A[idx])   break;
            m /= A[idx];
            n *= A[idx];
        }
        used[idx] = 0;
    }
}
int main() {
    sieve();
    int m, cases = 0;
    while (scanf("%d", &m) == 1 && m) {
        A.clear();
        for (int i = 0; i < Pt && (P[i]-1)*(P[i]-1) <= m; i++) {
            if (m%(P[i] - 1) == 0)
                A.push_back(P[i]);
        }
        ret = INF;
        dfs(m, 1, 0);
        printf("Case %d: %d %d\n", ++cases, m, ret);
    }
    return 0;
}