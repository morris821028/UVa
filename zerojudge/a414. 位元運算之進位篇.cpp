#include <stdio.h>

int main() {
    unsigned int n, m;
    while(scanf("%u", &n) == 1 && n) {
        m = n+1;
        n = n^m;
        int cnt = 0;
        while(n) {
            n -= n&(-n);
            cnt++;
        }
        printf("%d\n", cnt-1);
    }
    return 0;
}
