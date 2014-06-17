#include <stdio.h>
#include <stdlib.h>
int a[5005], b[5005], n;
int chk(int rank) {
    int i, sa = 0, sb = 0;
    int dif1, dif2, lea = 0;
    for(i = 0; i < n; i++) {
        sa += a[i];
        sb += b[i];
        if(sa > rank)   dif1 = sa - rank;
        else dif1 = 0;
        if(sb > rank)   dif2 = sb - rank;
        else dif2 = 0;

        if(dif1 + dif2 > lea)
            return 0;

        if(sa == 0 && sb > 0)
            sb--;
        else if(sb == 0 && sa > 0)
            sa--;
        else if(sa > 0 && sb > 0 && sa+sb > lea)
            lea++;
    }
    return 1;
}
int main() {
    int t, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &a[i], &b[i]);
        }
        int l = 1, r = 100000, m;
        while(l < r) {
            m = (l+r)>>1;
            if(chk(m))
                r = m;
            else
                l = m+1;
        }
        printf("%d\n", r-1);
    }
    return 0;
}
