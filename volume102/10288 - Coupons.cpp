#include <stdio.h>
#include <string.h>
long long gcd(long long x, long long y) {
    long long t;
    while(x%y) {
        t = x, x = y, y = t%y;
    }
    return y;
}
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        long long a = 0, b = 1; //a/b
        long long ta, tb, g;
        for(i = 1; i <= n; i++) {//n * sigma(1/i)
            ta = a*i+b;
            tb = b*i;
            g = gcd(ta, tb);
            a = ta/g;
            b = tb/g;
        }
        a *= n;
        g = gcd(a, b);
        a /= g, b /= g;
        if(b == 1)
            printf("%lld\n", a);
        else {
            char v[30], x[30], y[30];
            sprintf(v, "%lld", a/b);
            sprintf(x, "%lld", a%b);
            sprintf(y, "%lld", b);
            int vl = strlen(v), bl = strlen(y);
            for(i = 0; i <= vl; i++)
                putchar(' ');
            puts(x);
            printf("%s ", v);
            for(i = 0; i < bl; i++)
                putchar('-');
            puts("");
            for(i = 0; i <= vl; i++)
                putchar(' ');
            puts(y);
        }
    }
    return 0;
}
