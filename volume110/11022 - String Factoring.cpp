#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int dp[105][105];
char s[105];
int dfs(int l, int r) {
    if(l == r)
        return 1;
    if(dp[l][r])
        return dp[l][r];
    int i, j, k;
    int &ret = dp[l][r];
    ret = 0xfffffff;
    for(i = l; i < r; i++)
        ret = min(ret, dfs(l, i) + dfs(i+1, r));
    int sublen = r-l+1;
    for(i = 1; i <= sublen; i++) {
        if(sublen%i == 0) {
            for(k = l, j = 0; k <= r; k++) {
                if(s[k] != s[j+l])
                    break;
                j++;
                if(j >= i)  j = 0;
            }
            if(k == r+1 && r != l+i-1)
                ret = min(ret, dfs(l, l+i-1));
        }
    }
    return ret;
}
int main() {
    while(scanf("%s", s) == 1) {
        if(!strcmp(s, "*"))
            break;
        memset(dp, 0, sizeof(dp));
        int len = strlen(s);
        printf("%d\n", dfs(0, len-1));
    }
    return 0;
}
