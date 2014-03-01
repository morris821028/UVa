#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
    double l, r;
} DD;
int cmp(const void *i, const void *j) {
    DD *a, *b;
    a = (DD *)i, b = (DD *)j;
    return a->l < b->l ? -1 : 1;
}
int main() {
    int n, l, w;
    double x, r;
    int i, j;
    while(scanf("%d %d %d", &n, &l, &w) == 3) {
        int m = 0;
        DD D[10000];
        for(i = 0; i < n; i++) {
            scanf("%lf %lf", &x, &r);
            if(r > w/2.0) {
                double ll = x - sqrt(r*r - w*w/4.0);
                double rr = x + sqrt(r*r - w*w/4.0);
                D[m].l = ll, D[m].r = rr;
                m++;
            }
        }
        qsort(D, m, sizeof(DD), cmp);
        int ch, flag = 0;
        double right = 0;
        for(i = 0, j = 0; i < m; i++) {
            double tmp = right;
            ch = -1;
            while(j < m && D[j].l <= right) {
                if(D[j].r > tmp) {
                    tmp = D[j].r;
                    ch = j;
                }
                j++;
            }
            if(tmp >= l) {
                printf("%d\n", i+1);
                flag = 1;
                break;
            }
            if(ch == -1)
                break;
            right = tmp;
        }
        if(!flag)    puts("-1");
    }
    return 0;
}
