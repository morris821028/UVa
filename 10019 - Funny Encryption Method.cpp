#include <stdio.h>

int main() {
    int t;
    char s[10];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int x1, x2, b1 = 0, b2 = 0;
        sscanf(s, "%d", &x1);
        sscanf(s, "%x", &x2);
        while(x1)
            b1 += x1&1, x1 /= 2;
        while(x2)
            b2 += x2&1, x2 /= 2;
        printf("%d %d\n", b1, b2);
    }
    return 0;
}
