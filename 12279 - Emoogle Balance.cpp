#include <stdio.h>

int main() {
    int n, x, a, b, cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        a = b = 0;
        while(n--) {
            scanf("%d", &x);
            if(x)   a++;
            else    b++;
        }
        printf("Case %d: %d\n", ++cases, a-b);
    }
    return 0;
}
