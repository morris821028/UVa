#include <stdio.h>
#include <stdlib.h>
struct S {
    int x, y, i;
} D[10000], X[10000];
void Merge(int l, int m, int r) {
    int idx1 = l, idx2 = m+1;
    int i, j, t = 0;
    while(idx1 <= m && idx2 <= r) {
        if(D[idx1].x < D[idx2].x ||
           (D[idx1].x == D[idx2].x && D[idx1].y <= D[idx2].y))
            X[t++] = D[idx1++];
        else
            X[t++] = D[idx2++];
    }
    while(idx1 <= m)    X[t++] = D[idx1++];
    while(idx2 <= r)    X[t++] = D[idx2++];
    for(i = 0, j = l; i < t; i++, j++)
        D[j] = X[i];
}
void MergeSort(int l, int r) {
    if(l < r) {
        int m = (l+r)/2;
        MergeSort(l, m);
        MergeSort(m+1, r);
        Merge(l, m, r);
    }
}
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        int ans = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &D[i].x, &D[i].y);
            D[i].i = i;
        }
        MergeSort(0, n-1);
        for(i = 0; i < n; i++)
            ans += abs(D[i].i-i);
        printf("%d\n", ans);
    }
    return 0;
}
