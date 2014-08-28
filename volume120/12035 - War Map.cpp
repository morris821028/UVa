#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int n, A[32], B[32], totdeg;
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
    if (idx == n)
        return lsize >= lneed && rsize >= rneed && checkBipartite(Ldeg, lsize, Rdeg, rsize);
    Ldeg[lsize] = A[idx];
    if (dfs(idx+1, lsize+1, rsize, ldeg+A[idx], rdeg, lneed, max(rneed, A[idx])))
        return 1;
    Rdeg[rsize] = A[idx];
    
    if (idx > 0) {
    if (dfs(idx+1, lsize, rsize+1, ldeg, rdeg+A[idx], max(lneed, A[idx]), rneed))
        return 1;
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
        sort(A, A+n);
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