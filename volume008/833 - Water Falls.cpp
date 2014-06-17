#include <stdio.h>
#define inRange(c, l, r) ((c >= l && c <= r) || (c >= r && c <= l))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
struct seg {
    int sx, sy, ex, ey;
};
int main() {
    int t, m, n, q, i, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        seg s[100];
        for(i = 0; i < n; i++) {
            scanf("%d %d", &s[i].sx, &s[i].sy);
            scanf("%d %d", &s[i].ex, &s[i].ey);
        }
        scanf("%d", &q);
        while(q--) {
            scanf("%d %d", &x, &y);
            while(true) {
                int j = -1;
                double max = -1, ty;
                for(i = 0; i < n; i++) {
                    if(inRange(x, s[i].sx, s[i].ex)) {
                        ty = s[i].ey + (double)(s[i].sy-s[i].ey)*(x-s[i].ex)/(s[i].sx-s[i].ex);
                        if(ty < y) {
                            if(ty > max) {
                                max = ty;
                                j = i;
                            }
                        }
                    }
                }
                if(j == -1)  break;
                if((double)(s[j].sy-s[j].ey)/(s[j].sx-s[j].ex) < 0)
                    x = max(s[j].sx, s[j].ex);
                else
                    x = min(s[j].sx, s[j].ex);
                y = min(s[j].sy, s[j].ey);
            }
            printf("%d\n", x);
        }
        if(t)
            puts("");
    }
    return 0;
}
