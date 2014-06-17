#include <stdio.h>

int main() {
    int t;
    long long n;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld", &n);
        long long a, b;
        int cnt = 0;
        do {
            a = n;
            b = 0;
            while(n) {
                b = b*10 + n%10;
                n /= 10;
            }
            cnt++;
            n = a + b;
        } while(a != b);
        printf("%d %lld\n", cnt-1, a);
    }
    return 0;
}
