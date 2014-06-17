#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
char g[105][105];
int dp[105][105];
int main() {
    int testcase, n;
    int i, j, k, p, q;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        memset(dp, 0, sizeof(dp));
        vector<int> dpArgv[105][105];
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                if(g[i][j] != '*') {
                    dp[i][j] = 1;
                    dpArgv[i][j].push_back((i<<10)+j);
                }
            }
        }
        for(i = 2; i < n; i++) {
            for(j = 0; i+j < n; j++) {
                //dp[j][i+j] j:start, i+j:end
                for(p = j+1; p < i+j; p++) { //j->p ... q->i+j
                    for(q = p; q < i+j; q++) {
                        if(g[j][p] == g[q][i+j] && g[j][p] != '*') {
                            if(dp[p][q]+2 >= dp[j][i+j]) {
                                if(dp[p][q]+2 > dp[j][i+j])
                                    dpArgv[j][i+j].clear();
                                dp[j][i+j] = dp[p][q]+2;
                                dpArgv[j][i+j].push_back((p<<10)+q);
                            }
                        }
                    }
                }
            }
        }
        if(dp[0][n-1] == 0) {
            puts("NO PALINDROMIC PATH");
            continue;
        }
        int p, q, tp, tq;
        queue<int> X, Y, rX, rY;
        X.push(0), Y.push(n-1);
        char ansBuf[105];
        int ansIdx = 0;
        while(!X.empty()) {
            char mn = 127;
            while(!X.empty()) {
                p = X.front(), X.pop();
                q = Y.front(), Y.pop();
                rX.push(p), rY.push(q);
                for(i = 0; i < dpArgv[p][q].size(); i++) {
                    tp = dpArgv[p][q][i]>>10;
                    tq = dpArgv[p][q][i]&1023;
                    if(p == tp) {
                        if(g[p][q] < mn)
                            mn = g[p][q];
                    } else if(g[p][tp] < mn)
                        mn = g[p][tp];
                }
            }
            ansBuf[ansIdx++] = mn;
            while(!rX.empty()) {
                p = rX.front(), rX.pop();
                q = rY.front(), rY.pop();
                for(i = 0; i < dpArgv[p][q].size(); i++) {
                    tp = dpArgv[p][q][i]>>10;
                    tq = dpArgv[p][q][i]&1023;
                    if(g[p][tp] == mn) {
                        if(tp != tq && p+1 != q)
                            X.push(tp), Y.push(tq);
                    }
                }
            }
        }
        if(dp[0][n-1]&1) {//odd
            for(i = 0; i < ansIdx; i++)
                putchar(ansBuf[i]);
            for(i = ansIdx-2; i >= 0; i--)
                putchar(ansBuf[i]);
        } else {
            for(i = 0; i < ansIdx; i++)
                putchar(ansBuf[i]);
            for(i = ansIdx-1; i >= 0; i--)
                putchar(ansBuf[i]);
        }
        puts("");
    }
    return 0;
}
/*
3
4
*AAA
A*AA
AA*A
AAA*
5
*ABAC
A*CBD
BC*CB
ABC*A
CDBA*
5
*AXYZ
A*BQR
XB*BT
YQB*A
ZRTA*
*/
