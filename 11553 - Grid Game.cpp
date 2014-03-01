#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int g[10][10], dp[1024][1024], n;
char used[1024][1024];
int rec(int bit1, int bit2) {
    if(used[bit1][bit2])
        return dp[bit1][bit2];
    used[bit1][bit2] = 1;
    int& ans = dp[bit1][bit2];
    if(bit1 == (1<<n)-1)
        return (ans = 0);
    ans = -0xffffff;
    int i, j;
    for(i = 0; i < n; i++) {
        if(!((bit1>>i)&1)) {
            int tmp = 0xffffff;
            for(j = 0; j < n; j++) {
                if(!((bit2>>j)&1))
                    tmp = min(tmp, g[i][j]+rec(bit1|(1<<i), bit2|(1<<j)));
            }
            ans = max(ans, tmp);
        }
    }
    return ans;
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &g[i][j]);
        memset(used, 0, sizeof(used));
        printf("%d\n", rec(0, 0));
    }
    return 0;
}
