#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s[105][105];
int slen[105];
int calc(char a[], char b[]) {
    int i, j, k, ret = 0, cnt;
    for(i = 0; a[i]; i++) {
        cnt = 0;
        for(j = 0, k = i; b[j] && a[k]; j++, k++)
            if(a[k] == b[j])
                cnt++;
        ret = max(ret, cnt);

    }
    return ret;
}
int main() {
    int testcase;
    int n, i, j;

    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%s", &s[i]);
            slen[i] = strlen(s[i]);
        }
        int ans = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(i == j)  continue;
                if(slen[i] <= ans || slen[j] <= ans)
                    continue;
                int tmp = calc(s[i], s[j]);
                ans = max(ans, tmp);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
