#include <stdio.h>
int A[500000], X[500000];
long long merge(int l, int m, int r) {
    int idx1 = l, idx2 = m+1, top = 0;
    int i, j;
    long long cnt = 0, subans = 0;
    while(idx1 <= m && idx2 <= r) {
        if(A[idx1] <= A[idx2])
            X[top++] = A[idx1++], subans += cnt;
        else
            X[top++] = A[idx2++], cnt++;
    }
    while(idx1 <= m)    X[top++] = A[idx1++], subans += cnt;
    while(idx2 <= r)    X[top++] = A[idx2++];
    for(i = 0, j = l; i < top; i++, j++)
        A[j] = X[i];
    return subans;
}
void solve(int *A, int n) {
    int i, j;
    long long ans = 0;
    for(i = 1; i < n; i <<= 1) {
        for(j = 0; j < n; j += i) {
            if(j+i-1 < n)
                ans += merge(j, j+i/2-1, j+i-1);
            else
                ans += merge(j, j+i/2-1, n-1);
        }
    }
    ans += merge(0, i/2-1, n-1);
    printf("%lld\n", ans);
}
int main() {
    int n, i;
    while(scanf("%d", &n), n) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        solve(A, n);
    }
    return 0;
}
/*
100502205 資工2B Shiang-Yun Yang
測試地點：
Zerojudge - d542: 10810 - Ultra-QuickSort
UVa online judge 10810 - Ultra-QuickSort
使用非遞迴的 merge sort 完成。
*/
