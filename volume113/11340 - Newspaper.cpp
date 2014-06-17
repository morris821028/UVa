#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, i;
        long long $[256] = {}, v, ans = 0;
        char str[10001];
        scanf("%d ", &n);
        while(n--) {
            gets(str);
            sscanf(str+2, "%lld", &v);
            $[str[0]+128] = v;
        }
        scanf("%d ", &n);
        while(n--) {
            gets(str);
            for(i = 0; str[i]; i++)
                ans += $[str[i]+128];
        }
        printf("%lld.%02lld$\n", ans/100, ans%100);
    }
    return 0;
}
