#include <stdio.h>
#include <string.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
int tree[524289], M;
int A[262145];
void setTree() {
    int i;
    for(i = 2*M-1; i > 0; i--) {
        if(i >= M) {
            tree[i] = A[i-M];
        } else {
            tree[i] = min(tree[i<<1], tree[i<<1|1]);
        }
    }
}
int query(int s, int t) {
    static int i, ans;
    ans = 0xfffffff;
    for(s = s+M-1, t = t+M+1; (s^t) != 1; ) {
        if(~s&1) {
            ans = min(ans, tree[s^1]);
        }
        if(t&1) {
            ans = min(ans, tree[t^1]);
        }
        s >>= 1, t >>= 1;
    }
    return ans;
}
void clear(int s) {
    while(s > 0) {
        tree[s] = 0xfffffff;
        s >>= 1;
    }
}
void update(int s) {
    while(s > 0) {
        tree[s] = min(tree[s<<1], tree[s<<1|1]);
        s >>= 1;
    }
}
int main() {
    int n, m, i, j;
    char cmd[1000];
    while(scanf("%d %d", &n, &m) == 2) {
        for(M = 1; M < n+2; M <<= 1);
        memset(A, 63, sizeof(A));
        for(i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        setTree();
        getchar();
        int a[50], tmp, g, idx;
        while(m--) {
            gets(cmd);
            if(cmd[0] == 'q') {
                sscanf(cmd+6, "%d,%d", &i, &j);
                printf("%d\n", query(i, j));
            } else {
                tmp = 0, g = 0, idx = 0;
                for(i = 6; cmd[i]; i++) {
                    if(cmd[i] >= '0' && cmd[i] <= '9')
                        tmp = tmp*10 + cmd[i]-'0', g = 1;
                    else {
                        if(g) {
                            a[idx++] = tmp;
                            clear(tmp+M);
                        }
                        tmp = 0, g = 0;
                    }
                }
                tmp = A[a[0]];
                for(i = 1; i < idx; i++) {
                    A[a[i-1]] = A[a[i]];
                }
                A[a[idx-1]] = tmp;
                for(i = 0; i < idx; i++) {
                    tree[a[i]+M] = A[a[i]];
                    update((a[i]+M)>>1);
                }
            }
        }
    }
    return 0;
}
