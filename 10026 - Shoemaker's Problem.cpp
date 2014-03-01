#include <stdio.h>
#include <stdlib.h>
struct work {
    int s, t, v;
};
int cmp(const void *i, const void *j) {
    work *a, *b;
    a = (work *)i, b = (work *)j;
    if(a->t*b->s != b->t*a->s)
        return a->t*b->s - b->t*a->s;
    return a->v - b->v;
}
int main() {
    int t, i, n;
    work D[1001];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &D[i].t, &D[i].s);
            D[i].v = i+1;
        }
        qsort(D, n, sizeof(work), cmp);
        for(i = 0; i < n; i++) {
            if(i)
                putchar(' ');
            printf("%d", D[i].v);
        }
        puts("");
        if(t)
            puts("");
    }
    return 0;
}
