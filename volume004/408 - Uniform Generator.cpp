#include <stdio.h>
int gcd(int x, int y) {
    int t;
    while(x%y) {
        t = x, x = y, y = t%y;
    }
    return y;
}
int main() {
    int a, b;
    while(scanf("%d %d", &a, &b) == 2) {
        if(gcd(a, b) == 1)
            printf("%10d%10d    Good Choice\n", a, b);
        else
            printf("%10d%10d    Bad Choice\n", a, b);
        puts("");
    }
    return 0;
}
