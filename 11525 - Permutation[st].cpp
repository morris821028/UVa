#include <stdio.h>

int main() {
    int t, k, s, i, j, M;
    unsigned tree[150000];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &k);
        for(M = 1; M < k+1; M <<= 1);
        for(i = 2*M-1; i > 0; i--) {
            if(i >= M)
                tree[i] = 1;
            else
                tree[i] = tree[i<<1]+tree[i<<1|1];
        }
        int idx;
        for(i = 1; i <= k; i++) {
            scanf("%d", &s);
            s++;
            for(idx = 1; idx < M;) {
                if(tree[idx<<1] < s)
                    s -= tree[idx<<1], idx = idx<<1|1;
                else
                    idx = idx<<1;
            }
            if(i != 1)
                putchar(' ');
            printf("%d", idx-M+1);
            while(idx > 0)
                tree[idx]--, idx >>= 1;
        }
        puts("");
    }
    return 0;
}
