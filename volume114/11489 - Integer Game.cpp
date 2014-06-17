#include <stdio.h>

int main() {
    int t, cases = 0;
    char s[1005];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int cnt[10] = {}, i, sum = 0;
        for(i = 0; s[i]; i++) {
            cnt[s[i]-'0']++;
            sum += s[i]-'0';
        }
        int flag = 0;
        while(1) {
            for(i = sum%3; i < 10; i += 3) {
                if(cnt[i] != 0) {
                    cnt[i]--;
                    sum -= i;
                    break;
                }
            }
            if(i >= 10) break;
            flag = 1-flag;
        }
        printf("Case %d: %c\n", ++cases, flag ? 'S' : 'T');
    }
    return 0;
}
