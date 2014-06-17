#include <stdio.h>

int main() {
    int base, a, b;
    while(scanf("%d %d %d", &base, &a, &b) == 3) {
        int res = 1;
        int s = a*b;
        while(s != a) {
            s = s%base*b + s/base;
            res++;
        }
        printf("%d\n", res);
    }
    return 0;
}
