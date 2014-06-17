#include <stdio.h>
#include <string.h>
int ans[1<<12];
int dp(int n) {
    if(ans[n] != -1)
        return ans[n];
    int i, j = 0, tmp, x;
    ans[n] = 0xffff;
    for(i = 0; i < 10; i++) {
        if(((n>>i)&1) && ((n>>(i+1))&1) && !((n>>(i+2))&1)) {
            x = n;
            x ^= 1<<i;
            x ^= 1<<(i+1);
            x ^= 1<<(i+2);
            tmp = dp(x);
            if(tmp < ans[n])    ans[n] = tmp;
            j = 1;
        }
        if(!((n>>i)&1) && ((n>>(i+1))&1) && ((n>>(i+2))&1)) {
            x = n;
            x ^= 1<<i;
            x ^= 1<<(i+1);
            x ^= 1<<(i+2);
            tmp = dp(x);
            if(tmp < ans[n])    ans[n] = tmp;
            j = 1;
        }
    }
    if(j == 0) {
        ans[n] = 0;
        for(i = 0; i < 12; i++)
            if((n>>i)&1)    ans[n]++;
    }
    return ans[n];
}
int main() {
    memset(ans, -1, sizeof(ans));
    int t, i, n;
    char s[20];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        n = 0;
        for(i = 0; i < 12; i++)
            if(s[i] == 'o')
                n |= 1<<i;
        printf("%d\n", dp(n));
    }
    return 0;
}
