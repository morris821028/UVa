#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t, n, tn;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int S[305], T[305], i, j, k;
        map<int, int> r;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &S[i], &T[i]);
            r[S[i]] = 1;
            r[T[i]] = 1;
        }
        i = 0;
        for(map<int, int>::iterator it = r.begin();
            it != r.end(); it++) {
            it->second = i;
            i++;
        }
        tn = i+1;
        int dp[601][601] = {};
        char has[601][601] = {};
        for(i = 0; i < n; i++) {
            has[r[S[i]]][r[T[i]]] = 1;
        }
        int ans = 1;
        for(i = 0; i < tn; i++) {
            for(j = 0; j+i < tn; j++) {
                dp[j][j+i] = 0;
                if(i)
                    dp[j][j+i] = max(dp[j+1][j+i], dp[j][j+i-1]);
                for(k = j; k <= j+i; k++) {
                    dp[j][j+i] = max(dp[j][j+i], dp[j][k]+dp[k][j+i]);
                }

                dp[j][j+i] += has[j][j+i];
                if(dp[j][j+i] > ans)
                    ans = dp[j][j+i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
