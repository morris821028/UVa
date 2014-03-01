#include <stdio.h>
#include <queue>
using namespace std;

int main() {
    int L, U, R, cases = 0;
    int RV[20];
    while(scanf("%d %d %d", &L, &U, &R) == 3) {
        if(!L && !U && !R)
            break;
        int i, tmp;
        for(i = 0; i < R; i++)
            scanf("%d", &RV[i]);
        short dp[10000] = {};
        queue<int> Q;
        dp[L] = 1;
        Q.push(L);
        while(!Q.empty()) {
            if(dp[U])   break;
            L = Q.front(), Q.pop();
            for(i = 0; i < R; i++) {
                tmp = L+RV[i];
                if(tmp >= 10000)    tmp -= 10000;
                if(dp[tmp] == 0) {
                    dp[tmp] = dp[L]+1;
                    Q.push(tmp);
                }
            }
        }
        printf("Case %d: ", ++cases);
        if(dp[U])
            printf("%d\n", dp[U]-1);
        else
            puts("Permanently Locked");
    }
    return 0;
}
