#include <stdio.h>
#include <stdlib.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

int cmp(const void *i, const void *j) {
    return *(int *)i - *(int *)j;
}
int main() {
    int n, m, Case = 0, A[1000], B[25], C[25];
    int i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        scanf("%d", &m);
        int tmp;
        for(i = 0; i < m; i++) {
            scanf("%d", &B[i]);
            C[i] = 0xffffff;
        }
        qsort(A, n, sizeof(int), cmp);
        for(k = 0; k < m; k++) {
            for(i = 0; i < n; i++) {
                for(j = i+1; j < n; j++) {
                    tmp = A[i]+A[j];
                    if(abs(tmp-B[k]) <= abs(C[k]))
                        C[k] = tmp-B[k];
                    if(tmp-B[k] >= abs(C[k]))
                        break;
                }
            }
        }
        printf("Case %d:\n", ++Case);
        for(i = 0; i < m; i++) {
            printf("Closest sum to %d is %d.\n", B[i], B[i]+C[i]);
        }
    }
    return 0;
}
