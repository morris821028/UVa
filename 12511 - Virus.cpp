#include <stdio.h>

int main() {
    int t, n, m, a[1505], b[1505];
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
        scanf("%d", &m);
        for(i = 0; i < m; i++)
            scanf("%d", &b[i]);
        int LCIS[1505] = {};
        for(i = 0; i < n; i++) {
            int tmp = 0;
            for(j = 0; j < m; j++) {
                if(a[i] == b[j] && LCIS[j] < tmp+1)
                    LCIS[j] = tmp+1;
                if(a[i] > b[j] && LCIS[j] > tmp)
                    tmp = LCIS[j];
            }
        }
        int res = 0;
        for(i = 0; i < m; i++)
            if(LCIS[i] > res)
                res = LCIS[i];
        printf("%d\n", res);
    }
    return 0;
}
