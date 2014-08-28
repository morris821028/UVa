#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int n, m, A[32], B[32], totdeg;
pair<int, int> C[32];
int Ldeg[32], Rdeg[32];

int checkBipartite(int Ldeg[], int L, int Rdeg[], int R) {
    priority_queue<int> pQ;
    int x, cc = 0;
    for (int i = 0; i < R; i++)
        pQ.push(Rdeg[i]);
    for (int i = 0; i < L; i++)
        B[cc++] = Ldeg[i];
    sort(B, B+L, greater<int>());
    for (int i = 0; i < L; i++) {
        queue<int> Q;
        while (B[i] && !pQ.empty()) {
            B[i]--;
            x = pQ.top(), pQ.pop();
            x--;
            if (x)
                Q.push(x);
        }
        if (B[i])
            return 0;
        while (!Q.empty())
            pQ.push(Q.front()), Q.pop();
    }
    return pQ.empty();
}
int dfs(int idx, int lsize, int rsize, int ldeg, int rdeg, int lneed, int rneed) {
    if (ldeg > totdeg/2 || rdeg > totdeg/2)
        return 0;
    if (lneed + rneed > n || lsize + n - idx < lneed || rsize + n - idx < rneed)
        return 0;
    if (idx == m)
        return lsize >= lneed && rsize >= rneed && checkBipartite(Ldeg, lsize, Rdeg, rsize);
    for (int i = idx == 0; i <= C[idx].second; i++) {
        int l = i, r = C[idx].second - i, ln = lneed, rn = rneed;
        for (int j = 0; j < l; j++)
            Ldeg[lsize+j] = C[idx].first, rn = max(rn, C[idx].first);
        for (int j = 0; j < r; j++)
            Rdeg[rsize+j] = C[idx].first, ln = max(ln, C[idx].first);
        if (dfs(idx+1, lsize+l, rsize+r, ldeg+C[idx].first*l, rdeg+C[idx].first*r, ln, rn)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        totdeg = 0;
        for (int i = 0; i < n; i++)
            totdeg += A[i];
        sort(A, A+n, greater<int>());
        m = 0;
        C[m] = make_pair(A[0], 1), m++;
        for (int i = 1; i < n; i++) {
            if (A[i] == C[m-1].first)
                C[m-1].second++;
            else
                C[m] = make_pair(A[i], 1), m++;
        }
        int flag = totdeg%2 == 0 && dfs(0, 0, 0, 0, 0, 0, 0);
        printf("Case %d: %s\n", ++cases, flag ? "YES" : "NO");
    }
    return 0;
}

/*
 10000
 6
 3 0 2 2 3 0
 12
 0 0 0 0 0 0 0 0 0 0 0 0
 20
 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19
 4
 3 1 3 3
 5
 1 2 1 1 3
 4
 2 3 2 3
 7
 4 1 2 3 1 2 3
 */