#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct A {
  int n, v;
};
int cmp(const void *i, const void *j) {
    A *a, *b;
    a = (A *)i, b = (A *)j;
    if(a->v != b->v)
        return b->v - a->v;
    return b->n - a->n;
}
int main() {
    int t, n, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        A D[500];
        for(i = 0; i < n; i++) {
            scanf("%d", &D[i].n);
            int sqr = (int)sqrt(D[i].n);

            D[i].v = 0;
            for(j = 1; j <= sqr; j++)
                if(D[i].n%j == 0) {
                    D[i].v += 2;
                }
            if(sqr * sqr == D[i].n)
                D[i].v --;
        }
        qsort(D, n, sizeof(A), cmp);
        n = n-1;
        while(D[n].v == 2)
            n--;
        for(i = 0; i <= n; i++) {
            if(i)
                printf(" ");
            printf("%d", D[i].n);
        }
        puts("");
    }
    return 0;
}
