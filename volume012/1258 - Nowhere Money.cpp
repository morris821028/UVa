#include <stdio.h>

int main() {
    int i;
    long long f[100] = {0,1,2};
    for(i = 3; i <= 90; i++)
        f[i] = f[i-1]+f[i-2];
    long long n;
    while(scanf("%lld", &n) == 1) {
        long long a[100], b[100], ct = 0;
        printf("%lld\n", n);
        for(i = 90; i >= 1; i--)
            if(f[i] <=  n) {
                n -= f[i];
                a[ct] = f[i];
                b[ct++] = i;
            }
        for(i = 0; i < ct; i++)
            printf("%lld ", b[i]);
        puts("");
        for(i = 0; i < ct; i++)
            printf("%lld ", a[i]);
        puts("\n");
    }
    return 0;
}
