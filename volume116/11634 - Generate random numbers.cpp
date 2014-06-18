#include <stdio.h>

int main() {
    int n, cnt;
    while(scanf("%d", &n) == 1 && n) {
        char m[10000] = {};
        cnt = 0;
        while(m[n] == 0) {
            cnt++;
            m[n] = 1;
            n = n*n;
            n /= 100;
            n %= 10000;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
