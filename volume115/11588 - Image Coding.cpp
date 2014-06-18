#include <stdio.h>

int main() {
    int t, cases = 0;
    int r, c, m, n, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d %d", &r, &c ,&m, &n);
        char s[50];
        int cnt[26] = {};
        for(j = 0; j < r; j++) {
            scanf("%s", s);
            for(i = 0; s[i]; i++)
                cnt[s[i]-'A']++;
        }
        int mx = 0, mxi = 0;
        for(i = 0; i < 26; i++) {
            if(cnt[i] > mx)
                mx = cnt[i], mxi = 0;
            if(cnt[i] == mx)
                mxi++;
        }
        printf("Case %d: %d\n", ++cases, mx * mxi * m + (r*c - mx*mxi) * n);
    }
    return 0;
}
