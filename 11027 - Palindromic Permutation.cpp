#include <stdio.h>
#include <string.h>
int main() {
    int t, cases = 0;
    long long pk;
    char s[105];
    scanf("%d", &t);
    long long f[30] = {1};
    int i, j, k;
    for(i = 1; i < 20; i++)
        f[i] = f[i-1]*i;
    while(t--) {
        scanf("%s %lld", s, &pk);
        printf("Case %d: ", ++cases);
        int len = strlen(s);
        int cntA[26] = {};
        int odd = 0, oddi;
        for(i = 0; i < len; i++)
            cntA[s[i]-'a']++;
        for(i = 0; i < 26; i++) {
            if(cntA[i]%2)   odd++, oddi = i;
            cntA[i] /= 2;
        }
        if(odd > 1) {
            puts("XXX");
            continue;
        }
        len /= 2;
        char res[105];
        int pre;
        long long comb = f[len];
        for(i = 0; i < 26; i++)
            comb /= f[cntA[i]];
        if(comb < pk) {
            puts("XXX");
            continue;
        }
        for(i = 0; i < len; i++) {
            for(j = 0, pre = 0; j < 26; j++) {
                if(cntA[j]) {
                    long long comb = f[len-i-1];
                    cntA[j]--;
                    for(k = 0; k < 26; k++)
                        comb /= f[cntA[k]];
                    cntA[j]++;
                    pre = j;
                    pk -= comb;
                    if(pk <= 0) {
                        pk += comb;
                        break;
                    }
                }
            }
            while(cntA[pre] == 0)
                pre++;
            res[i] = pre+'a';
            cntA[pre]--;
        }
        if(odd) {
            res[len] = oddi+'a';
            for(i = 0; i < len; i++)
                res[len+i+1] = res[len-i-1];
            res[2*len+1] = '\0';
        } else {
            for(i = 0; i < len; i++)
                res[2*len-i-1] = res[i];
            res[2*len] = '\0';
        }
        puts(res);
    }
    return 0;
}
