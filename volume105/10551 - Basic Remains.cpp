#include <stdio.h>
#include <string.h>
int main() {
    int n, m;
    char s[1001], a[20];
    while(scanf("%d", &n) == 1 && n) {
        scanf("%s %s", s, a);
        int i, len = strlen(a), tmp = 1;
        m = 0;
        for(i = len-1; i >= 0; i--) {
            m += (a[i]-'0')*tmp;
            tmp *= n;
        }
        tmp = 0;
        for(i = 0; s[i]; i++) {
            tmp = tmp*n + s[i]-'0';
            tmp %= m;
        }
        int ans[50], at = -1;
        while(tmp) {
            ans[++at] = tmp%n;
            tmp /= n;
        }
        for(i = at; i >= 0; i--)
            printf("%d", ans[i]);
        if(at == -1)
            printf("0");
        puts("");
    }
    return 0;
}
