#include <stdio.h>
#include <stdlib.h>
int cmp(const void *i, const void *j) {
    return *(int *)i - *(int *)j;
}
int main() {
    int t, n, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int A[10000];
        for(i = 0; i < n; i++) {
            scanf("%d", A+i);
            if(i)
                A[i] += A[i-1];
        }
        qsort(A, n, sizeof(int), cmp);
        int ans = 0, last = A[0], tmp = 1;
        for(i = 1; i < n; i++) {
            if(A[i] != last) {
                if(tmp > ans)   ans = tmp;
                last = A[i], tmp = 1;
            } else
                tmp++;
        }
        if(tmp > ans)   ans = tmp;
        printf("%d\n", ans);
    }
    return 0;
}
