#include <stdio.h>

int main() {
    int t, cases = 0, n, k;
    char d[505];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &k);
        scanf("%s", d);
        int r[26] = {}, cnt = 0, i;
        for(i = 0; i < 26; i++)
            r[i] = -0xfff;
        for(i = 0; i < n; i++) {
            if(i-r[d[i]-'A'] <= k)
                cnt++;
            r[d[i]-'A'] = i;
        }
        printf("Case %d: %d\n", ++cases, cnt);
    }
    return 0;
}
