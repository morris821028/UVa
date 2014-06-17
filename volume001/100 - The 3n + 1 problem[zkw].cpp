#include <stdio.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define swap(x, y) {int tmp; tmp = x, x = y, y = tmp;}
#define N 1000000
#define node 1048576
int A[node], tree[node<<1], M;
void setTree(int s, int t) {
    int i;
    for(i = 2*M-1; i > 0; i--) {
        if(i >= M) { //leaf
            tree[i] = A[i-M];
        } else {
            tree[i] = max(tree[i<<1], tree[(i<<1)+1]);
        }
    }
}
int query(int s, int t) {
    static int i;
    int ans = 0;
    for(s = s+M-1, t = t+M+1; (s^t) != 1;) {
        if(~s&1) {
            ans = max(ans, tree[s^1]);
        }
        if(t&1) {
            ans = max(ans, tree[t^1]);
        }
        s >>= 1, t >>= 1;
    }
    return ans;
}
void build() {
    long long n;
    int i, len;
    A[1] = 1;
    for(i = 2; i <= N; i++) {
        n = i, len = 1;
        while(n != 1) {
            if(n&1) {
                n = n*3 + 1;
            } else {
                n >>= 1;
            }
            if(n < i) {
                len += A[n];
                break;
            }
            len ++;
        }
        A[i] = len;
    }
    for(M = 1; M < N+2; M <<= 1);
    setTree(0, M-1);
}
int main() {
    build();
    int i, j;
    while(scanf("%d %d", &i, &j) == 2) {
        printf("%d %d ", i, j);
        if(i > j)
            swap(i, j);
        printf("%d\n", query(i, j));
    }
    return 0;
}
