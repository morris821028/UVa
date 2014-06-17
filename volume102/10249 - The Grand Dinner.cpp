#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int c, i;
} DD;
int cmp(const void *i, const void *j) {
    DD *x, *y;
    x = (DD *)i, y = (DD *)j;
    if(x->c != y->c)
        return y->c - x->c;
    return x->i - y->i;
}
int cmp1(const void *i, const void *j) {
    return *(int *)i - *(int *)j;
}
int main() {
    int n, m, i, j, B[70];
    DD A[70];
    DD D[50];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)    break;
        for(i = 0; i < n; i++)
            scanf("%d", &A[i].c), A[i].i = i, B[i] = A[i].c;
        for(i = 0; i < m; i++)
            scanf("%d", &D[i].c), D[i].i = i;
        int ans[70][70];
        qsort(A, n, sizeof(DD), cmp);
        for(i = 0; i < n; i++) {
            qsort(D, m, sizeof(DD), cmp);
            int tmp = A[i].c, idx = 0, err = 0;
            for(j = 0; j < m; j++) {
                if(tmp == 0)    break;
                if(D[j].c == 0) {
                    err = 1;
                    break;
                } else {
                    D[j].c--;
                    tmp--;
                    ans[A[i].i][idx++] = D[j].i;
                }
            }
            if(err || tmp) break;
        }
        if(i == n) {
            puts("1");
            for(i = 0; i < n; i++) {
                qsort(ans[i], B[i], sizeof(int), cmp1);
                printf("%d", ans[i][0]+1);
                for(j = 1; j < B[i]; j++)
                    printf(" %d", ans[i][j]+1);
                puts("");
            }
        } else
            puts("0");
    }
    return 0;
}
