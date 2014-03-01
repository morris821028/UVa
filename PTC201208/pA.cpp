#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int p, t, q;
}DD;
DD D[10000];
int cmp(const void *i, const void *j) {
    DD *a, *b;
    a = (DD *)i, b = (DD *)j;
    return a->t - b->t;
}
int main() {
    int t, t1, t2, k1, k2, n;
    int i, p, tt, q;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d %d %d", &t1, &t2, &k1, &k2, &n);
        for(i = 0; i < n; i++) {
            scanf("%d-%d-%d", &p, &tt, &q);
            D[i].p = p, D[i].t = tt, D[i].q = q;
        }
        qsort(D, n, sizeof(DD), cmp);
        int mm[1000] = {}, flag = 0, j = 0;
        for(i = 0; i < n; i++) {
            while(j < n && D[j].t < D[i].t-t1) {
                if(D[j].q == 1)
                    mm[D[j].p]--;
                j++;
            }
            if(D[i].q == 1) {
                mm[D[i].p]++;
                if(mm[D[i].p] >= k1)
                    flag = 1;
            }
        }
        j = 0;
        int total = 0;
        for(i = 0; i < n; i++) {
            while(j < n && D[j].t < D[i].t-t2) {
                if(D[j].q == 1)
                    total--;
                j++;
            }
            if(D[i].q == 1) {
                total++;
                if(total >= k2)
                    flag = 1;
            }
        }
        puts(flag ? "ALARM" : "GOOD");
    }
    return 0;
}
/*
3
2 1 2 3 6
000-0000000-1
000-0000001-1
001-0000000-0
001-0000002-0
003-0000003-0
001-0000000-0
2 1 2 3 6
000-0000000-0
000-0000001-1
001-0000000-0
001-0000001-1
003-0000001-1
006-0000001-0
2 1 2 3 6
000-0000000-0
000-0000001-1
001-0000000-0
005-0000001-0
001-0000009-0
011-0000001-0
*/
