#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;
int A[50], n, tn;
set<int> dp;
void dfs(int idx, int st, int val) {
    if(idx == n) {
        if(dp.find(val) == dp.end() && st == 0) {
            tn++;
            dp.insert(val);
        }
        return;
    }
    if(st)
        dfs(idx+1, 0, A[idx]);
    else
        dfs(idx+1, 0, val&A[idx]);
    dfs(idx+1, 0, val|A[idx]);
    dfs(idx+1, st, val);
}
int main() {
    int t, i, j;
    int cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        dp.clear();
        tn = 0;
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        dfs(0, 1, 0);
        printf("Case #%d: %d\n", ++cases, tn-n);
    }
    return 0;
}
