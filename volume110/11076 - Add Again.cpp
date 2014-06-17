#include <stdio.h>

int main() {
    int n, i;
    unsigned long long f[20] = {1};
    for(i = 1; i < 20; i++)
        f[i] = f[i-1] * i;
    while(scanf("%d", &n) == 1 && n) {
        int dec[10] = {}, x, sum = 0;
        for(i = 0; i < n; i++)
            scanf("%d", &x), dec[x]++, sum += x;
        unsigned long long C = f[n], tmp = 0, d10 = 1;
        for(i = 0; i < 10; i++)
            C /= f[dec[i]];
        for(i = 0; i < n; i++) {
            tmp += d10;
            d10 = d10*10;
        }
        C = C*sum/n*tmp;
        printf("%llu\n", C);
    }
    return 0;
}
