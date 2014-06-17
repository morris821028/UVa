#include <stdio.h>

int main() {
    int t, n, x;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int max = 0, min = 99;
        while(n--) {
            scanf("%d", &x);
            if(x > max) max = x;
            if(x < min) min = x;
        }
        printf("%d\n", (max-min)*2);
    }
    return 0;
}
