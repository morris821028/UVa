#include <stdio.h>

int main() {
    int n, cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        int a, b, c;
        long long res = 0;
        for(a = n/3; a >= 1; a--) {
            b = a+1;
            c = b+1;
            if(a+b+c <= n) {
                c--;
                res += (n-a-b-c+1)/2;
            }
        }
        printf("Case %d: %lld\n", ++cases, res);
    }
    return 0;
}
