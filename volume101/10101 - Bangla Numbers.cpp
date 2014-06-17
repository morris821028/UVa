#include <stdio.h>
void trans(long long n) {
    static long long m[4] = {10000000, 100000, 1000, 100};
    static char x[4][6] = {"kuti", "lakh", "hajar", "shata"};
    int i;
    for(i = 0; i < 4; i++) {
        if(n >= m[i]) {
            trans(n/m[i]);
            printf(" %s", x[i]);
            n %= m[i];
        }
    }
    if(n)   printf(" %lld", n);
}
int main() {
    long long n;
    int cases = 0;
    while(scanf("%lld", &n) == 1) {
        printf("%4d.", ++cases);
        if(n == 0)  printf(" 0");
        trans(n);
        puts("");
    }
    return 0;
}
