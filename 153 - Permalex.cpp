#include <stdio.h>
#include <string.h>
int gcd(int x, int y) {
    int t;
    while(x%y) {
        t = x, x = y, y = t%y;
    }
    return y;
}
int main() {
    char s[50];
    while(scanf("%s", s) == 1) {
        if(s[0] == '#')
            break;
        int cnt[26] = {}, len = strlen(s);
        int i, j, k, l, a;
        for(i = 0; s[i]; i++) {
            cnt[s[i]-'a']++;
        }
        long long ans = 0;
        for(i = 0; s[i]; i++) {
            for(j = 0; j < s[i]-'a'; j++) {
                if(cnt[j] == 0) continue;
                cnt[j]--;
                int set[50] = {};
                for(k = 2; k < len-i; k++)
                    set[k] = k;
                for(k = 0; k < 26; k++) {
                    for(l = 2; l <= cnt[k]; l++) {
                        int tmp = l;
                        for(a = 2; a < len-i; a++) {
                            int g = gcd(tmp, set[a]);
                            tmp /= g;
                            set[a] /= g;
                        }
                    }
                }
                long long tmp = 1;
                for(k = 2; k < len-i; k++)
                    tmp *= set[k];
                ans += tmp;
                cnt[j]++;
            }
            cnt[s[i]-'a']--;
        }
        printf("%10lld\n", ans+1);
    }
    return 0;
}
