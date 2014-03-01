#include <stdio.h>
#include <stdlib.h>
struct ab {
    int a, b, c;
};
ab D[500000];
int cmp(const void *i, const void *j) {
    ab *a, *b;
    a = (ab *)i, b = (ab *)j;
    if(a->a != b->a)
        return a->a - b->a;
    return a->b - b->b;
}
int main() {
    int n, i, a, b;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            scanf("%d %d", &a, &b);
            if(a > b)
                D[i].a = b, D[i].b = a, D[i].c = 1;
            else
                D[i].a = a, D[i].b = b, D[i].c = 0;
        }
        qsort(D, n, sizeof(ab), cmp);
        int ta = 0, tb = 0, flag = 0;
        for(i = 0; i < n; i++) {
            if(!D[i].c) ta++;
            else        tb++;
            if(i == n-1 || D[i].a != D[i+1].a && D[i].b != D[i+1].b) {
                if(ta != tb)
                    flag = 1;
                ta = 0, tb = 0;
            }
        }
        if(flag)
            puts("NO");
        else
            puts("YES");
    }
    return 0;
}
