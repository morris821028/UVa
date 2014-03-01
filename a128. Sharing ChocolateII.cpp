#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
using namespace std;
map<int, int> R[65536]; // R[state][l][w]
int dp[65536], N, n, m;
void dfs(int);
bool findflag;
bool check(int l, int w) {
    if(l == n && w == m)    findflag = true;
    if(w == n && l == m)    findflag = true;
    return !(max(l, w) > max(n, m) || min(l, w) > min(n, m));
}
void dfs2(int state, int idx, int a, int b) {
    if(findflag)    return;
    int la, lb, wa, wb;
    if(idx == N) {
        if(a == 0 || b == 0 || a < b)    return;
        dfs(a), dfs(b);
        //printf("%d %d %d\n", state, a, b);
        if(state == (1<<N)-1)   puts("app");
        map<int, int>::iterator it, jt;
        /*for(it = R[a].begin(); it != R[a].end(); it++) {
            if
            for(jt = R[b].begin(); jt != R[b].end(); jt++) {
                la = it->first, wa = it->second;
                lb = jt->first, wb = jt->second;
                if(la == lb && check(la, wa+wb))
                    R[state][la] = wa+wb;
                if(la == wb && check(la, wa+lb))
                    R[state][la] = wa+lb;
                if(wa == wb && check(wa, la+lb))
                    R[state][wa] = la+lb;
                if(wa == lb && check(wa, la+wb))
                    R[state][wa] = la+wb;
            }
        }*/
        return;
    }
    if((state>>idx)&1) {
        dfs2(state, idx+1, a|(1<<idx), b);
        dfs2(state, idx+1, a, b|(1<<idx));
    } else
        dfs2(state, idx+1, a, b);
}
void dfs(int state) {
    if(findflag)    return;
    if(dp[state])   return;
    dfs2(state, 0, 0, 0);
}
int main() {
    int A[20];
    int i, j, k, cases = 0;
    while(scanf("%d", &N) == 1 && N) {
        scanf("%d %d", &n, &m);
        int sum = 0;
        for(i = 0; i < N; i++) {
            scanf("%d", &A[i]);
            sum += A[i];
        }
        printf("Case %d: ", ++cases);
        if(sum != n*m) {
            puts("No");
            continue;
        }
        int state = (1<<N)-1;
        for(i = 0; i <= state; i++)
            R[i].clear(), dp[i] = 0;
        for(i = 0; i < N; i++) {
            for(j = 1; j <= A[i]; j++) {
                if(A[i]%j == 0) {
                    if(!check(A[i]/j, j))
                        continue;
                    R[1<<i][A[i]/j] = j;
                    R[1<<i][j] = A[i]/j;
                }
            }
            dp[1<<i] = 1;
        }
        findflag = false;
        dfs(state);
        findflag = (R[state].find(n) != R[state].end());
        if(findflag)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
/*
15
1 15
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
0
*/
