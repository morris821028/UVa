#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int n, k;
    int i, j;
    while(scanf("%d %d", &n, &k) == 2) {
        if(n == 0 && k == 0)
            break;
        if(k == 0 || n == 1) {
            puts("1");
            continue;
        }
        int row1[20] = {}, row2[20] = {};
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++)
                if((i+j)%2)
                    row1[(i+j)/2]++;
                else
                    row2[(i+j)/2]++;
        }
        sort(row1, row1+n-1);
        sort(row2, row2+n);
        int dp1[20][20] = {}, dp2[20][20] = {};
        dp1[0][0] = 1, dp1[0][1] = row1[0];
        dp2[0][0] = 1, dp2[0][1] = row2[0];
        for(i = 1; i < n-1; i++) {
            dp1[i][0] = 1;
            for(j = 1; j <= row1[i]; j++)
                dp1[i][j] = dp1[i-1][j] + dp1[i-1][j-1]*(row1[i]-(j-1));
        }
        for(i = 1; i < n; i++) {
            dp2[i][0] = 1;
            for(j = 1; j <= row2[i]; j++)
                dp2[i][j] = dp2[i-1][j] + dp2[i-1][j-1]*(row2[i]-(j-1));
        }
        int ans = 0;
        for(i = 0; i <= k; i++)
            ans += dp1[n-2][i]*dp2[n-1][k-i];
        printf("%d\n", ans);
    }
    return 0;
}
