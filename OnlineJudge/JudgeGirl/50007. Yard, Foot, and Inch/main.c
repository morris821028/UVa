#include <stdio.h>
#include <assert.h>
#include "length.h"
 
int main() {
    int a[3] = {-1, -1, -1}, b[3] = {-1, -1, -1};
    int c[3] = {-1, -1, -1}, d[3] = {-1, -1, -1};
    int e[3] = {-1, -1, -1}, f[3] = {-1, -1, -1};
    int cmd, x, y, z;
    scanf("%d", &cmd);
    if (cmd == 1) {
        init(a);
        printf("%d %d %d\n", a[0], a[1], a[2]);
    } else if (cmd == 2) {
        init(a);
        scanf("%d", &x);
        add(a, x);
        printf("%d %d %d\n", a[0], a[1], a[2]);
    } else if (cmd == 3) {
        init(a), init(b);
        scanf("%d %d", &x, &y);
        add(a, x), add(b, y);
        sum(a, b, c);
        printf("%d %d %d\n", c[0], c[1], c[2]);
    } else if (cmd == 4) {
        init(a), init(b), init(c), init(d);
        scanf("%d %d %d", &x, &y, &z);
        assert(x+y >= z);
        add(a, x), add(b, y);
        sum(a, b, c);
        add(d, z);
        diff(c, d, e);
        printf("%d %d %d\n", e[0], e[1], e[2]);
    }
    return 0;
}
