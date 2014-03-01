#include <stdio.h>
int A[1048576], X[1048576];
long long ret = 0;
void merge(int l, int m, int r) {
    int idx1 = l, idx2 = m+1;
    int top = 0, i, j;
    long long D = 0;
    while(idx1 <= m && idx2 <= r) {
        if(A[idx1] <= A[idx2])
            X[top++] = A[idx1++], ret += D;
        else
            X[top++] = A[idx2++], D++;
    }
    while(idx1 <= m)
        X[top++] = A[idx1++], ret += D;
    while(idx2 <= r)
        X[top++] = A[idx2++];
    for(i = 0, j = l; i < top; i++, j++)
        A[j] = X[i];
}
void mergeSort(int l, int r) {
    if(l < r) {
        int m = (l+r)/2;
        mergeSort(l, m);
        mergeSort(m+1, r);
        merge(l, m, r);
    }
}
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        ret = 0;
        mergeSort(0, n-1);
        printf("%lld\n", ret);
    }
    return 0;
}
