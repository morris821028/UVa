#include <stdio.h>
#include <string.h>
#define max(x,y) ((x)>(y)?(x):(y))
void modify(int idx, int l, int val, int T[]) {
    while(idx <= l) {
        T[idx] = max(T[idx], val);
        idx += idx&(-idx);
    }
}
int query(int idx, int T[]) {
    int r = 0;
    while(idx) {
        r = max(r, T[idx]);
        idx -= idx&(-idx);
    }
    return r;
}
int l[200005], r[200005], bit[200005];
int A[200005], pos[200005];
int main() {
    int t, n, i, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = n-1; i >= 0; i--) {
            scanf("%d", &A[i]);
            bit[i+1] = 0;
            pos[i] = 0;
        }
        for(i = 0; i < n; i++) {
            x = n-A[i]+1;
            y = query(x, bit);
            l[i] = y;
            modify(x, n, y+1, bit);
        }
        int lis = query(n, bit);
        for(i = 0; i <= n; i++)
            bit[i] = 0;
        for(i = n-1; i >= 0; i--) {
            x = A[i];
            y = query(x, bit);
            r[i] = y;
            modify(x, n, y+1, bit);
        }
        for(i = 0; i < n; i++) {
            if(l[i]+r[i]+1 == lis) {
                pos[l[i]]++;
            }
        }
        int cnt = 0, ans = 0;
        for(i = n-1; i >= 0; i--) {
            if(l[i]+r[i]+1 == lis) {
                if(pos[l[i]] == 1) {
                    //printf("%d %d +\n", n-i, cnt+1);
                    cnt++;
                    ans ^= n-i+cnt;
                }
            }
        }
        printf("%d %d\n", cnt, ans);
        //printf("%d\n", lis);
    }
    return 0;
}
