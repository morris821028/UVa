#include <stdio.h>

int main() {
    int t, x;
    scanf("%d", &t);
    while(t--) {
        int l, n, min = 0, max = 0;
        scanf("%d %d", &l, &n);
        while(n--) {
            scanf("%d", &x);
            x = x < l-x ? x : l-x;
            if(x > min)
                min = x;
            if(l-x > max)
                max = l-x;
        }
        printf("%d %d\n", min, max);
    }
    return 0;
}
