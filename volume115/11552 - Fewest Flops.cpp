#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int mn(int x, int y) {
    if(x == -1)
        return y;
    return x < y ? x : y;
}
int main() {
    scanf("%*d");
    char s[1005];
    int K, i, j, k, l;
    while(scanf("%d %s", &K, s) == 2) {
        int len = strlen(s);
        int dp[2][26] = {}, flag = 1, mnn;
        for(i = 0; i < 26; i++)
            dp[0][i] = -1;
        for(i = 0; i < len; i += K) {
            sort(s+i, s+i+K);
            s[0] = s[i]-'a';
            for(j = 1, k = 0; j < K; j++)
                if(s[i+j]-'a' != s[k])
                    s[++k] = s[i+j]-'a';
            mnn = 0xffff;
            /*for(j = 0; j <= k; j++)
                printf("%c", s[j]+'a');
            puts("");*/
            for(j = 0; j < 26; j++) {
                dp[flag][j] = -1;
                if(dp[!flag][j] != -1)
                    mnn = min(mnn, dp[!flag][j]);
            }
            if(mnn == 0xffff)   mnn = 0;
            if(k == 0) {
                dp[flag][s[0]] = mnn+1;
                if(dp[!flag][s[0]] != -1)
                    dp[flag][s[0]] = mn(dp[flag][s[0]], dp[!flag][s[0]]);
                flag = !flag;
                continue;
            }
            for(j = 0; j <= k; j++) {
                if(dp[!flag][s[j]] != -1) {
                    for(l = 0; l <= k; l++) {
                        if(l == j) {}
                        else
                            dp[flag][s[l]] = mn(dp[flag][s[l]], dp[!flag][s[j]]+k);
                    }
                }
            }
            for(j = 0; j <= k; j++)
                dp[flag][s[j]] = mn(dp[flag][s[j]], mnn+k+1);
            /*for(j = 0; j < 26; j++)
                printf("%d ", dp[flag][j]);
            puts("");*/
            flag = !flag;
        }
        mnn = 0xffff;
        for(i = 0; i < 26; i++)
            if(dp[!flag][i] != -1)
                mnn = min(mnn, dp[!flag][i]);
        printf("%d\n", mnn);
    }
    return 0;
}
/*
2
5 helloworldlllll
/hello/ordwl/lllll => 8
*/
