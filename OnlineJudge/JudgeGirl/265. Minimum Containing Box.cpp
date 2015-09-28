#include <stdio.h>
#define MIN(x,y) (x) < (y) ? (x) : (y)
#define MAX(x,y) (x) > (y) ? (x) : (y)
int main() {
    int x, y, rx, ry, lx, ly;
    scanf("%d %d", &rx, &ry), lx = rx, ly = ry;
    while (scanf("%d %d", &x, &y) == 2) {
        rx = MAX(rx, x), lx = MIN(lx, x);
        ry = MAX(ry, y), ly = MIN(ly, y);
    }
    printf("%d\n", (rx - lx)*(ry - ly));
    return 0;
}