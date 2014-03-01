#include <stdio.h>

int main() {
    int t, n, Case = 0;
    char str[101];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        scanf("%s", str);
        int i, ans = 0, tmp = 0;
        for(i = 0; str[i]; i++) {
            if(str[i] == '.') {
                tmp ++;
                if(tmp == 3) {
                    ans++;
                    tmp = 0;
                }
            } else {
                if(tmp == -1) {
                    tmp = 0;
                } else if(tmp == 1) {
                    ans++;
                    tmp = -1;
                } else if(tmp == 2) {
                    ans++;
                    tmp = 0;
                }
            }
        }
        if(tmp > 0) ans++;
        printf("Case %d: %d\n", ++Case, ans);
    }
    return 0;
}
