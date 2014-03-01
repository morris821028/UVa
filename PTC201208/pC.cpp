#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int i, j;
    int t, A[50];
    int V, m, ans;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &V, &m);
        int used[50] = {};
        for(i = 0; i < m; i++) {
            scanf("%d", &A[i]);
        }
        sort(A, A+m, greater<int>());
        int flag = 0, ans[50], at = 0;
        while(1) {
            int dp[10001] = {}, sour[10001] = {};
            dp[0] = 1;
            for(i = 0; i < m; i++) {
                if(used[i] == 0)
                for(j = V-A[i]; j >= 0; j--) {
                    if(dp[j+A[i]] == 0 && dp[j] == 1) {
                        dp[j+A[i]] = 1;
                        sour[j+A[i]] = i;
                    }
                }
            }
            int tmpN = V;
            while(tmpN >= 0 && dp[tmpN] == 0)   tmpN--;
            if(tmpN  == 0)  break;
            flag = 1;
            ans[at++] = tmpN;
            while(tmpN) {
                used[sour[tmpN]] = 1;
                tmpN -= A[sour[tmpN]];
            }
        }
        sort(ans, ans+at);
        for(i = at-1; i >= 0; i--) {
            printf("%s%d", i == at-1 ? "" : " ", ans[i]);
        }
        puts("");
    }
    return 0;
}
