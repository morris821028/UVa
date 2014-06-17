#include <stdio.h>

int main() {
    char s;
    long long ans = 0;
    while(s = getchar()) {
        if(s == -1)
            break;
        if(s == '1' || s == '0') {
            ans = (ans<<1)+s-'0';
            if(ans >= 131071)
                ans %= 131071;
        } else if(s == '#') {
            puts(ans ? "NO" : "YES");
            ans = 0;
        }
    }
    return 0;
}
