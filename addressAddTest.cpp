#include <stdio.h>

int main() {
    int k = 5, *p = &k;
    printf("%d %d\n", p, p+3);
    return 0;
}
