#include <stdio.h>

int main() {
    int n, k;
    while(scanf("%d %d", &n, &k) == 2) {
        int a, b, pa, pb, ta, tb, tk;
        pa = 0, pb = 1, a = 1, b = n;
        while(--k) {
            tk = (n+pb)/b;
            ta = tk*a - pa;
            tb = tk*b - pb;
            pa = a, pb = b;
            a = ta, b = tb;
        }
        printf("%d/%d\n", a, b);
    }
    return 0;
}
