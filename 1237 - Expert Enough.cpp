#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, m, p;
        int l[10000], h[10000];
        int i;
        char name[10000][25];
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%s %d %d", name[i], &l[i], &h[i]);
        scanf("%d", &m);
        while(m--) {
            scanf("%d", &p);
            int cnt = 0, mi;
            for(i = 0; i < n; i++) {
                if(l[i] <= p && p <= h[i])
                    cnt++, mi = i;
                if(cnt > 1) break;
            }
            if(cnt == 1)
                puts(name[mi]);
            else
                puts("UNDETERMINED");
        }
        if(t)
            puts("");
    }
    return 0;
}
