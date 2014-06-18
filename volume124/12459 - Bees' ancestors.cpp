#include <stdio.h>

int main() {
    long long f[81] ={1,1};
    int i;
    for(i = 2; i <= 80; i++)
        f[i] = f[i-1] + f[i-2];
    while(scanf("%d", &i) == 1 && i)
        printf("%lld\n", f[i]);
    return 0;
}
