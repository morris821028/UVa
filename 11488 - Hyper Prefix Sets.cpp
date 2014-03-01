#include <stdio.h>
struct ND {
    int l, r, cnt;
};
ND BUF[1000000];
int ans;
void sol(int nd, int dep) {
    if(BUF[nd].l)
        sol(BUF[nd].l, dep+1);
    if(BUF[nd].r)
        sol(BUF[nd].r, dep+1);
    if(dep*BUF[nd].cnt > ans)
        ans = dep*BUF[nd].cnt;
}
int main() {
    int t, n, i, j;
    char bin[205];
    scanf("%d", &t);
    while(t--) {
        scanf("%d ", &n);
        int size = 0, idx;
        BUF[0].l = BUF[0].r = BUF[0].cnt = 0;
        for(i = 0; i < n; i++) {
            gets(bin);
            idx = 0;
            for(j = 0; bin[j]; j++) {
                if(bin[j] == '0') {
                    if(BUF[idx].l == 0) {
                        BUF[idx].l = ++size;
                        BUF[size].l = BUF[size].r = BUF[size].cnt = 0;
                    }
                    idx = BUF[idx].l;
                } else {
                    if(BUF[idx].r == 0) {
                        BUF[idx].r = ++size;
                        BUF[size].l = BUF[size].r = BUF[size].cnt = 0;
                    }
                    idx = BUF[idx].r;
                }
                BUF[idx].cnt++;
            }
        }
        ans = 0;
        sol(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
