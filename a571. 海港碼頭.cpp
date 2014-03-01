#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, tn;
    while(scanf("%d", &n) == 1) {
        int S[105], T[105], i, j, k;
        map<int, int> r;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &S[i], &T[i]);
            r[S[i]] = 1, r[T[i]] = 1;
        }
        i = 0;
        for(map<int, int>::iterator it = r.begin();
            it != r.end(); it++) {
            it->second = i;
            i++;
        }
        tn = i+1;
        int dp[210][210] = {};
        char has[210][210] = {};
        for(i = 0; i < n; i++) {
            dp[r[S[i]]][r[T[i]]] = 1;
            has[r[S[i]]][r[T[i]]] = 1;
        }
        int ans = 1;
        for(i = 0; i < tn; i++) {
            for(j = 0; j+i < tn; j++) {
                if(i)
                    dp[j][j+i] = max(max(dp[j+1][j+i], dp[j][j+i-1]), dp[j][j+i]);
                for(k = j; k < j+i; k++) {
                    dp[j][j+i] = max(dp[j][j+i], dp[j][k]+dp[k+1][j+i]);
                    dp[j][j+i] = max(dp[j][j+i], dp[j+1][k]+dp[k+1][j+i-1]+has[j][j+i]);
                }
                if(dp[j][j+i] > ans)
                    ans = dp[j][j+i];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
