#include <stdio.h>
int main() {
    int dp[1<<12] = {};
    int i, j, state;
    int lk[24] = {1<<0,1<<1,1<<2,1<<3,1<<4,1<<5,1<<6,
                1<<7,1<<8,1<<9,1<<10,1<<11,1<<0|1<<3,
                1<<1|1<<4,1<<2|1<<3,1<<3|1<<4,1<<4|1<<5,
                1<<3|1<<7,1<<4|1<<8,1<<6|1<<7,1<<7|1<<8,
                1<<8|1<<9,1<<7|1<<10,1<<8|1<<11};
    dp[0] = 1;
    for(i = 0; i < 4096; i++) {
        for(j = 0; j < 24; j++) {
            if((i&lk[j]) == lk[j]) {
                dp[i] |= !dp[i-lk[j]];
            }
        }
    }
    int n;
    char s[50];
    while(scanf("%d", &n) == 1) {
        while(n--) {
            scanf("%s", s);
            int state = 0;
            for(i = 0; s[i]; i++)
                state += (s[i]-'0')<<i;
            printf("%d", dp[state]);
        }
        puts("");
    }
    return 0;
}
