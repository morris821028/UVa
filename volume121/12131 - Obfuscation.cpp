#include <stdio.h>
#include <map>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;
char s[1005], word[10005][105];
struct E {
    int v, idx;
};
int main() {
    int t, n, i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        scanf("%d", &n);
        map<string, E> W;
        map<string, E>::iterator it;
        for(i = 0; i < n; i++) {
            scanf("%s", word[i]);
            string tmp(word[i]);
            sort(tmp.begin(), tmp.end());
            tmp = tmp + word[i][0] + word[i][strlen(word[i])-1];
            it = W.find(tmp);
            if(it == W.end())
                W[tmp].v = 1, W[tmp].idx = i;
            else
                W[tmp].v++;
        }
        int dp[1505] = {}, m = strlen(s);
        int arg_dp[1505][2] = {};
        dp[0] = 1;
        for(i = 0; i < m; i++) {
            if(dp[i])
            for(j = 1; j < 105 && i+j <= m; j++) {
                char tmp = s[i+j];
                s[i+j] = '\0';
                string buf(s+i);
                sort(buf.begin(), buf.end());
                buf = buf + s[i] + s[i+j-1];
                it = W.find(buf);
                if(it != W.end()) {
                    dp[i+j] += dp[i]*(it->second.v);
                    if(dp[i+j] > 2) dp[i+j] = 2;
                    arg_dp[i+j][0] = i;
                    arg_dp[i+j][1] = it->second.idx;
                }
                s[i+j] = tmp;
            }
        }
        if(dp[m] == 0)
            puts("impossible");
        else if(dp[m] == 2)
            puts("ambiguous");
        else {
            int buf[10005];
            int bidx = 0;
            while(m) {
                buf[bidx++] = arg_dp[m][1];
                m = arg_dp[m][0];
            }
            printf("%s", word[buf[bidx-1]]);
            for(i = bidx-2; i >= 0; i--)
                printf(" %s", word[buf[i]]);
            puts("");
        }
    }
    return 0;
}
