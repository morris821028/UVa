#include <stdio.h>
#include <string.h>
#define node 262144
int A[node], tree[node<<1], M;
void setTree() {
    int i;
    for(i = 2*M-1; i > 0; i--) {
        if(i >= M) { //leaf
            tree[i] = A[i-M];
        } else {
            tree[i] = tree[i<<1]+tree[(i<<1)+1];
        }
    }
}
int query(int s, int t) {
    static int i;
    int ans = 0;
    for(s = s+M-1, t = t+M+1; (s^t) != 1;) {
        if(~s&1)
            ans += tree[s^1];
        if(t&1)
            ans += tree[t^1];
        s >>= 1, t >>= 1;
    }
    return ans;
}
void singleModify(int s, int v) {
    s += M;
    while(s) {
        tree[s] += v;
        s >>= 1;
    }
}
int main() {
    int n, x, y, i;
    int cases = 0;
    char op[10], cmd[50];
    while(scanf("%d", &n) == 1 && n) {
        for(M = 1; M < n+2; M <<= 1);
        memset(A, 0, sizeof(A));
        for(i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        while(getchar() != '\n');
        if(cases)   puts("");
        printf("Case %d:\n", ++cases);
        setTree();
        while(gets(cmd)) {
            if(cmd[0] == 'E')
                break;
            sscanf(cmd, "%s %d %d", op, &x, &y);
            if(op[0] == 'M')
                printf("%d\n", query(x, y));
            else {
                singleModify(x, y-A[x]);
                A[x] = y;
            }
        }
    }
    return 0;
}
