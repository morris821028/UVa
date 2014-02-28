#include <stdio.h>
#include <string.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define swap(x, y) {int tmp; tmp = x, x = y, y = tmp;}
#define N 1000000
#define node 1048576
int A[N+1], tree[node<<1];
void setTree(int l, int r, int k) {
    if(l == r)
        tree[k] = A[l];
    if(l < r) {
        int m = (l+r) >> 1;
        setTree(l, m, k<<1);
        setTree(m+1, r, (k<<1)+1);
        tree[k] = max(tree[k<<1], tree[(k<<1)+1]);
    }
}
int getTree(int l, int r, int k, int i, int j) {
    if(l == i && r == j)
        return tree[k];
    if(l < r) {
        int m = (l+r) >> 1;
        if(m >= j)
            return getTree(l, m, k<<1, i, j);
        else if(m < i)
            return getTree(m+1, r, (k<<1)+1, i, j);
        else
            return max(getTree(l, m, k<<1, i, m), getTree(m+1, r, (k<<1)+1, m+1, j));
    }
}
void build() {
    long long n;
    int i, len;
    memset(A, 0, sizeof(A));
    memset(tree, 0, sizeof(tree));
    A[1] = 1;
    for(i = 2; i <= N; i++) {
        n = i, len = 1;
        while(n != 1) {
            if(n&1) {
                n = n*3 + 1;
            } else {
                n >>= 1;
            }
            if(n < N && A[n] != 0) {
                len += A[n];
                break;
            }
            len ++;
        }
        A[i] = len;
    }
    setTree(1, N, 1);
}
int main() {
    build();
    int i, j;
    while(scanf("%d %d", &i, &j) == 2) {
        printf("%d %d ", i, j);
        if(i > j)
            swap(i, j);
        printf("%d\n", getTree(1, N, 1, i, j));
    }
    return 0;
}
