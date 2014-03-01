#include <stdio.h>
#include <stdlib.h>
int A[100005], B[100005];
void calcAB(int n) {
    int i, j, k, l;
    int &a = A[n], &b = B[n];
    a = 1, b = 1;
    for(i = 2; i*i <= n; i++) {
        if(n%i == 0) {
            l = i, k = 1;
            j = 0;
            while(n%i == 0) {
                k += l, l *= i;
                n /= i, j++;
            }
            a *= j+1;
            b *= k;
        }
    }
    if(n != 1)
        a *= 2, b *= n+1;
}
int main() {
    int i, a, b, k;
    for(i = 1; i <= 100000; i++)
        calcAB(i);
    scanf("%*d");
    while(scanf("%d %d %d", &a, &b, &k) == 3) {
        while(a%k)  a++;
        long long g = 0, h = 0;
        for(i = a; i <= b; i += k)
            g += A[i], h += B[i];
        printf("%lld %lld\n", g, h);
    }
    return 0;
}
