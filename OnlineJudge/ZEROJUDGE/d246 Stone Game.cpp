#include <stdio.h>

int main() {
    int n, k;
    while(scanf("%d %d", &n, &k) == 2) {
        int res = 0, p;
        while(n--) {
            scanf("%d", &p);
            res ^= p%(k+1);
        }
        puts(res ? "Yes" : "No");
    }
    return 0;
}
