#include <stdio.h>

int main() {
    int t, tmp, a, b, c;
    int Case = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &a, &b, &c);
        if(a > c)
            tmp = a, a = c, c = tmp;
        if(b > c)
            tmp = b, b = c, c = tmp;
        if(a > b)
            tmp = a, a = b, b = tmp;
        printf("Case %d: %d\n", ++Case, b);
    }
    return 0;
}
