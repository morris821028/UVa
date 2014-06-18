#include <stdio.h>
#include <string.h>
char s[1005];
int cnt[1005];
int greedy(int r, int n) {
    int i;
    int pre = -1;
    int one = 0, zero = 0;
    for(i = 0; i <= n; i++) {
        if(s[i] == '?') {
            if(cnt[i]&1) { // odd
                if(pre < 0 || i == n) {
                    if(1 > r)   return 0;
                } else if(s[i-1] == s[i+1]) {
                    if(1 > r)   return 0;
                    zero = one = 0;
                } else {
                    if(s[i-1] == '0') {
                        if(zero+1 <= r) {
                            zero++;
                            zero = 0;
                        } else {
                            one++;
                        }
                    } else {
                        if(one+1 <= r) {
                            one++;
                            one = 0;
                        } else {
                            zero++;
                        }
                    }
                }
            } else { // even
                if(pre < 0 || i == n) {
                    if(1 > r)   return 0;
                } else if(s[i-1] == s[i+1]) {
                    if(2 > r)   return 0;
                    zero = one = 0;
                } else {
                    if(1 > r)   return 0;
                    zero = one = 0;
                }
            }
        } else {
            pre = s[i];
            if(s[i] == '0')
                zero += cnt[i], one = 0;
            else
                one += cnt[i], zero = 0;
        }
        //printf("%d %d - %d %c\n", one, zero, i, s[i]);
        if(one > r || zero > r)
            return 0;
    }
    return 1;
}
int main() {
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int n = strlen(s), i, j;
        for(i = 0, j = -1; i < n; i++) {
            if(i == 0 || s[i] != s[j])
                s[++j] = s[i], cnt[j] = 1;
            else
                cnt[j]++;
        }
        /*for(i = 0; i <= n; i++)
            printf("%d %c\n", cnt[i], s[i]);*/
        int l = 0, r = n, m, f;
        n = j;
        for(r = 1; ; r++) {
            if(greedy(r, n)) {
                break;
            }
        }
        printf("Case %d: %d\n", ++cases, r);
    }
    return 0;
}
/*
10
0?1
00?1
00?11
0?11
0??1
0???1
0????1
0?0
00?0
00?00
0??0
0???0
0????0
*/
