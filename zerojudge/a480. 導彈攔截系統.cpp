#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
typedef struct {
    int a, b;
} E;
E D[1000005];
bool cmp(E i, E j) {
    return i.a < j.a;
}
int main() {
    int x1, x2, y1, y2, x, y;
    int n, i, j;
    while(scanf("%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            D[i].a = (x-x1)*(x-x1)+(y-y1)*(y-y1);
            D[i].b = (x-x2)*(x-x2)+(y-y2)*(y-y2);
        }
        sort(D, D+n, cmp);
        for(i = n-2; i >= 0; i--)
            D[i].b = max(D[i].b, D[i+1].b);
        int ans = 2147483647;
        for(i = 0; i < n; i++) {
            int p = D[i].a;
            int tmp = 0;
            if(i != n-1)    tmp = D[i+1].b;
            p = D[i].a + tmp;
            ans = ans < p ? ans : p;
        }
        ans = ans < D[0].b ? ans : D[0].b;
        printf("%d\n", ans);
    }
    return 0;
}
