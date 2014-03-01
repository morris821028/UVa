#include <stdio.h>
int f1 = 1, f2 = 1, f3;
int i, j;
int A[305] = {0,1}, cycle;
int C[305];
void build() {
    for(i = 2; ; i++) {
        if(f1 == 1 && f2 == 1 && i != 2)
            break;
        A[i] = f2;
        f3 = f1 + f2;
        f1 = f2, f2 = f3%100;
    }
    cycle = i-2;
    for(i = 1; i <= cycle; i++)
        C[i] = C[i-1] + A[i];
}
long long get(long long n) {
    return n/cycle*C[cycle] + C[n%cycle];
}
int main() {
    build();
    int testcase;
    long long L, R;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%lld %lld", &L, &R);
        printf("%lld\n", get(R)-get(L-1));
    }
    return 0;
}
