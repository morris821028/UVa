#include <stdio.h>
#include <string.h>
int main() {
    int testcase;
    char s[10], s2[10], format[20] = "%0?d";
    int A, B;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%s %d %d", s, &A, &B);
        int len = strlen(s);
        int c = 1, i, j;
        for(i = 0; i < len; i++)
            c = c*10;
        format[2] = len+'0';
        int ret = 0;
        for(i = c/10; i < c; i++) {
            sprintf(s2, format, i);
            int cnt[10] = {}, ta = 0, tb = 0;
            int err = 0;
            for(j = 0; j < len; j++) {
                cnt[s2[j]-'0']++;
                if(s2[j] == '0')
                    err = 1;
            }
            if(err) continue;
            for(j = 0; j < len && ta <= A; j++) {
                if(s[j] == s2[j]) {
                    ta++;
                    cnt[s[j]-'0']--;
                }
            }
            if(ta != A) continue;
            for(j = 0; j < len && tb <= B; j++) {
                if(s[j] != s2[j]) {
                    if(cnt[s[j]-'0']) {
                        tb++;
                        cnt[s[j]-'0']--;
                    }
                }
            }
            if(ta == A && tb == B)
                ret++;
        }
        printf("%d\n", ret);
    }
    return 0;
}
