#include <stdio.h>
#include <math.h>

long long trailpow(long long n, int k) {
    if(k == 0)  return 1;
    if(k&1)
        return n*trailpow(n*n%1000, k>>1)%1000;
    return trailpow(n*n%1000, k>>1);
}
int main() {
    scanf("%*d");
    int n, k;
    while(scanf("%d %d", &n, &k) == 2) {
        int trail = trailpow(n, k);
        printf("%d...%03d\n", (int)(pow(10, fmod(k*log10(n), 1))*100), trail);
    }
    return 0;
}
