#include <stdio.h>
int gcd(int a, int b) {
    int tmp, flag = 0;
    int x1 = 1, y1 = 0, x2 = 0, y2 = 1;
    while(a%b) {
        if(flag) {
            x2 -= a/b*x1;
            y2 -= a/b*y1;
        } else {
            x1 -= a/b*x2;
            y1 -= a/b*y2;
        }
        tmp = a, a = b, b = tmp%b;
        flag ^= 1;
    }
    if(flag)
        printf("%d %d", x1, y1);
    else
        printf("%d %d", x2, y2);
    printf(" %d\n", b);
    return b;
}
int main() {
    int A, B;
    while(scanf("%d %d", &A, &B) == 2) {
        gcd(A, B);
    }
    return 0;
}
