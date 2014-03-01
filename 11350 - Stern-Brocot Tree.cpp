#include <stdio.h>

int main() {
    int t;
    char str[100];
    scanf("%d ", &t);
    while(t--) {
        gets(str);
        unsigned long long la = 0, lb = 1, ma = 1, mb = 1, ra = 1, rb = 0;
        unsigned long long x = 1, y = 1, i;
        for(i = 0; str[i]; i++) {
            if(str[i] == 'L') {
                x = la+ma, y = lb+mb;
                ra = ma, rb = mb;
                ma = x, mb = y;
            } else {
                x = ra+ma, y = rb+mb;
                la = ma, lb = mb;
                ma = x, mb = y;
            }
        }
        printf("%llu/%llu\n", x, y);
    }
    return 0;
}
