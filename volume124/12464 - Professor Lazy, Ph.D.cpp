#include <stdio.h>

int main() {
    int n, a, b;
    long long m;
    while(scanf("%d %d %lld", &a ,&b, &m) == 3) {
        if(m == 0 && a == 0 && b == 0)
            break;
        n = m%5;
        if(n == 0)
            printf("%d\n", a);
        if(n == 1)
            printf("%d\n", b);
        if(n == 2)
            printf("%d\n", (1+b)/a);
        if(n == 3)
            printf("%d\n", (a+b+1)/a/b);
        if(n == 4)
            printf("%d\n", (a+1)/b);
    }
    return 0;
}
