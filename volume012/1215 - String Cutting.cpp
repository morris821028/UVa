#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;
int main() {
    int t, c[1005], n;
    char s[10005];
    int i, j, k, ci;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &c[i]);
        scanf("%s", s);
        int len = strlen(s), ans = 0;
        set<int> S;
        S.insert(0);
        S.insert(len);
        for(i = 0; i < n; i++) {
            ci = c[i];
            set<int>::iterator it = S.lower_bound(ci);
            int l, r;
            r = *it;
            it--, l = *it;
            char s1[26] = {}, s2[26] = {};
            for(j = ci-1; j >= l; j--)
                s1[s[j]-'a'] = 1;
            for(j = ci; j < r; j++)
                s2[s[j]-'a'] = 1;
            //puts(" s2");
            for(j = 0; j < 26; j++)
                if(s1[j]^s2[j])
                    ans++;
            S.insert(ci);
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
2
3
5 6 5
ababccd
2
4 2
ababcd
*/
