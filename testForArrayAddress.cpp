#include <stdio.h>

int main() {
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int *b;
    b = a;
    printf("%d %d\n", &a[1], b+1);
    printf("%d %d\n", a[2], &b+2);
    printf("%d %d\n", a[3], *(b+3));
    return 0;
}
