#include <stdio.h>
#include <string.h>

int main() {
    int n, m, i, j, c, cases = 0;
    char name[20][100];
    char a[100], b[100];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        for(i = 0; i < n; i++)
            scanf("%s", name[i]);
        int cnt[20] = {};
        while(m--) {
            scanf("%s %s %d", a, b, &c);
            for(i = 0; i < n; i++)
                if(!strcmp(a, name[i]))
                    break;
            cnt[i] += c;
            for(i = 0; i < n; i++)
                if(!strcmp(b, name[i]))
                    break;
            cnt[i] -= c;
        }
        printf("Case #%d\n", ++cases);
        while(1) {
            int maxx = 0, minx = 0xffffff;
            int idx1, idx2;
            for(i = 0; i < n; i++) {
                if(cnt[i] > maxx)
                    maxx = cnt[i], idx1 = i;
                if(cnt[i] < minx)
                    minx = cnt[i], idx2 = i;
            }
            if(maxx == 0)   break;
            if(maxx >= -minx) {
                printf("%s %s %d\n", name[idx2], name[idx1], -minx);
                int tmp = -minx;
                cnt[idx1] -= tmp;
                cnt[idx2] += tmp;
            } else {
                printf("%s %s %d\n", name[idx2], name[idx1], maxx);
                int tmp = maxx;
                cnt[idx1] -= tmp;
                cnt[idx2] += tmp;
            }
        }
        puts("");
    }
    return 0;
}
