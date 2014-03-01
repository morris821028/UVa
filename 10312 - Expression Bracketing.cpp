#include <stdio.h>
long long s[30] = {};
long long S(int n) {
    if(n <= 2)   return 1;
    if(n == 3)   return 3;
    if(s[n])     return s[n];
    s[n] = ((6*n-9)*S(n-1)-(n-3)*S(n-2))/n;
    return s[n];
}
int main() {
    long long f[30] = {1, 1}, i, j;
    for(i = 2; i <= 30; i++)
        for(j = 0; j < i; j++)
            f[i] += f[j]*f[i-j-1];
    int n;
    while(scanf("%d", &n) == 1) {
        printf("%lld\n", S(n)-f[n-1]);
    }
    return 0;
}
