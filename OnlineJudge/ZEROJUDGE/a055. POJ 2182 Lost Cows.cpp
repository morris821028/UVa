#include <stdio.h>
#include <algorithm>
using namespace std;
const int MAXN = 131072<<1;
int A[MAXN], tree[MAXN], B[MAXN];
void build(int k, int l, int r) {
    if (l == r) {
        tree[k] = 1;
        return ;
    }
    int mid = (l+r)/2;
    build(k<<1, l, mid);
    build(k<<1|1, mid+1, r);
    tree[k] = tree[k<<1] + tree[k<<1|1];
}
int query(int k, int l, int r, int x) {
    tree[k]--;
    if (l == r) return l;
    int mid = (l+r)/2;
    if (tree[k<<1] >= x)
        return query(k<<1, l, mid, x);
    else
        return query(k<<1|1, mid+1, r, x - tree[k<<1]);
}
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        A[1] = 0;
        for (int i = 2; i <= n; i++)
            scanf("%d", &A[i]);
        build(1, 1, n);
        for (int i = n; i >= 1; i--)
            B[i] = query(1, 1, n, A[i]+1);
        for (int i = 1; i <= n; i++)
            printf("%d\n", B[i]);
    }
    return 0;
}