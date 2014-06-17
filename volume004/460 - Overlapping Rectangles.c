#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
typedef struct {
    int x, y;
} Point;
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        Point a, b, c, d;
        int i, j, k, l;
        scanf("%d %d %d %d", &a.x, &a.y, &b.x, &b.y);
        scanf("%d %d %d %d", &c.x, &c.y, &d.x, &d.y);
        i = max(a.x, c.x);
        j = max(a.y, c.y);
        k = min(b.x, d.x);
        l = min(b.y, d.y);
        if(i >= k || j >= l)
            puts("No Overlap");
        else
            printf("%d %d %d %d\n", i, j, k, l);

        if(t)
            puts("");
    }
    return 0;
}
