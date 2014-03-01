#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
typedef struct {
    int x, y;
} Pt;
int main() {
    int t, cases = 0, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        Pt a, b, c, d;
        int i, j, k, l, tmp;
        n--;
        scanf("%d %d %d %d", &a.x, &a.y, &b.x, &b.y);
        i = a.x, j = a.y, k = b.x, l = b.y;
        int flag = 0;
        while(n--) {
            scanf("%d %d %d %d", &c.x, &c.y, &d.x, &d.y);
            i = max(a.x, c.x), j = max(a.y, c.y);
            k = min(b.x, d.x), l = min(b.y, d.y);
            if(i >= k || j >= l) {
                flag = -1;
            } else {
                a.x = i, a.y = j, b.x = k, b.y = l;
            }
        }
        if(i >= k || j >= l)    flag = -1;
        printf("Case %d: ", ++cases);
        if(!flag)   printf("%d\n", (i-k)*(j-l));
        else    printf("0\n");
    }
    return 0;
}
