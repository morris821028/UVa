#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int main() {
    int n, cases = 0;
    char s[32];
    while (scanf("%d", &n) == 1) {
        int ret = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            int cnt[128] = {}, mcnt[32] = {};
            int diff = 0, same = 0;
            for (int j = 0; s[j]; j++)
                cnt[s[j]]++;
            for (int j = 'a'; j <= 'z'; j++) {
                if (cnt[j]) {
                    if (mcnt[cnt[j]] == 0)
                        diff++;
                    if (mcnt[cnt[j]] > 0)
                        same = 1;
                    mcnt[cnt[j]]++;
                }
            }
            if (diff > 1 && same == 0)
                ret++;
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}