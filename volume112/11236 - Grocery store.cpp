#include <stdio.h>
#include <math.h>
int main() {
    int a, b, c, d;
    long long p, s;
    for (a = 1; a+a+a+a <= 2000; a++)
    for (b = a; a+b+b+b <= 2000; b++)
    for (c = b; a+b+c+c <= 2000; c++) {
        p = (long long) a * b * c;
        s = a + b + c;
        if (p <= 1000000)
			continue;
        if ((s * 1000000) % (p - 1000000))
        	continue;
        d = (s * 1000000) / (p - 1000000);
        s += d;
        if (s > 2000 || d < c)   continue;
        printf("%d.%02d %d.%02d ", a/100, a%100, b/100, b%100);
        printf("%d.%02d %d.%02d\n", c/100, c%100, d/100, d%100);
    }
    return 0;
}
