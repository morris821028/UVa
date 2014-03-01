#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int e, f, c;
        scanf("%d %d %d", &e, &f, &c);
        e += f;
        int ans = 0;
        while(e >= c) {
            ans += e/c;
            e = e%c + e/c;
        }
        printf("%d\n", ans);
    }
    return 0;
}
