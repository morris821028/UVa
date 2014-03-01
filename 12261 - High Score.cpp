#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int main() {
    /*freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);*/
    int testcase;
    char s[1005];
    int cost[1005];
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%s", s);
        int n = strlen(s);
        int ret = 0, dp = 0;
        int i, j, k;
        for(i = 0; i < n; i++) {
            cost[i] = min(s[i]-'A', 26-(s[i]-'A'));
            ret += cost[i];
        }
        if(ret == 0) {
            puts("0");
            continue;
        }
        int pre = -1, count = 0;
        for(i = 0; i < n; i++) {
            if(cost[i]) {
                count ++;
                if(pre == -1)   {
                    pre = i;
                    dp = n-i;
                } else {
                    if(dp == 0) dp = 0xfffffff;
                    dp = min(dp, pre+pre + n-i);
                    dp = min(dp, n-i+n-i + pre);
                    pre = i;
                }
            }
        }
        if(count == 1)  dp = min(pre, n-pre);
        dp = min(dp, pre);
        printf("%d\n", ret + dp);
    }
    return 0;
}
