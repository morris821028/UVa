#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int in, v;
} Order;
int cmp(const void *i, const void *j) {
    Order *a, *b;
    a = (Order *)i, b = (Order *)j;
    if(a->v != b->v)
        return a->v - b->v;
    return a->in - b->in;
}
int main() {
    int t, n, m, i, j, k;
    char dna[101][101];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &m, &n);
        Order D[101];
        for(i = 0; i < n; i++) {
            scanf("%s", dna[i]);
            int sum = 0;
            for(j = 0; j < m; j++) {
                for(k = j+1; k < m; k++) {
                    if(dna[i][j] > dna[i][k]) {
                        sum++;
                    }
                }
            }
            D[i].v = sum, D[i].in = i;
        }
        qsort(D, n, sizeof(Order), cmp);
        for(i = 0; i < n; i++) {
            puts(dna[D[i].in]);
        }
        if(t)
            puts("");
    }
    return 0;
}
