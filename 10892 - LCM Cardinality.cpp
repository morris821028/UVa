#include <stdio.h>
#include <math.h>
#define LL long long
LL gcd(LL a, LL b) {
    static LL tmp;
    while(a%b) {
        tmp = a, a = b, b = tmp%b;
    }
    return b;
}
int main() {
    int n, i, j;
    while(scanf("%d", &n) == 1 && n) {
        int sq = (int)sqrt(n), A[2000], at = 0;
        for(i = 1; i <= sq; i++) {
            if(n%i == 0) {
                A[at++] = i;
                if(i*i != n)
                    A[at++] = n/i;
            }
        }
        int cnt = 0;
        for(i = 0; i < at; i++) {
            for(j = i; j < at; j++) {
                if((long long)A[i]/gcd(A[i], A[j])*A[j] == n)
                    cnt++;
            }
        }
        printf("%d %d\n", n, cnt);
    }
    return 0;
}
