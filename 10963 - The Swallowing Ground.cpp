#include <stdio.h>
#include <stdlib.h>

int main() {
    int t, n, x, y, d;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        scanf("%d %d", &x, &y), d = abs(x-y), n--;
        int flag = 1;
        while(n--) {
            scanf("%d %d", &x, &y);
            if(abs(x-y) != d)
                flag = 0;
        }
        puts(flag ? "yes" : "no");
        if(t)   puts("");
    }
    return 0;
}
