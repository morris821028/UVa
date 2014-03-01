#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
typedef struct {
    int x, y;
} Pt;
int main() {
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        Pt a, b, c, d;
        int i, j, k, l;
        scanf("%d %d %d %d", &a.x, &a.y, &b.x, &b.y);
        scanf("%d %d %d %d", &c.x, &c.y, &d.x, &d.y);
        i = max(a.x, c.x), j = max(a.y, c.y);
        k = min(b.x, d.x), l = min(b.y, d.y);
        int A = (b.x-a.x)*(b.y-a.y);
        int B = (d.x-c.x)*(d.y-c.y);
        int C = (i-k)*(j-l);
        printf("Night %d: ", ++cases);
        if(i >= k || j >= l) {
            printf("0 %d %d\n", A+B, 10000-A-B);
        } else {
            printf("%d %d %d\n", C, A+B-C-C, 10000-A-B+C);
        }
    }
    return 0;
}
