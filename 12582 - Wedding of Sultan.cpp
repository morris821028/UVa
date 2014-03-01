#include <stdio.h>
#include <string.h>

int main() {
    int t, cases = 0, i;
    scanf("%d", &t);
    while(t--) {
        char s[105];
        int ans[128] = {}, stk[128];
        int stkIdx = -1;
        scanf("%s", s);
        for(i = 0; s[i]; i++) {
            if(stkIdx < 0 || stk[stkIdx] != s[i]) {
                stk[++stkIdx] = s[i];
                ans[s[i]]++;
            } else {
                stkIdx--;
                if(stkIdx >= 0)
                    ans[stk[stkIdx]]++;
            }
        }
        ans[s[0]]--;
        printf("Case %d\n", ++cases);
        for(i = 'A'; i <= 'Z'; i++)
            if(ans[i])
                printf("%c = %d\n", i, ans[i]);
    }
    return 0;
}
