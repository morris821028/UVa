#include <stdio.h>

int main() {
    int t = 0, x, i, n, m, k;
    char f[513], str[10];
    while(scanf("%d", &n) == 1 && n) {
        printf("S-Tree #%d:\n", ++t);
        int fa[10], fb[10];
        for(i = 1; i <= n; i++) {
            scanf("%s", str);
            sscanf(str+1, "%d", &x);
            fa[x] = i;
        }
        scanf("%s", f);
        scanf("%d", &m);
        while(m--) {
            scanf("%s", str+1);
            for(i = 1; i <= n; i++)
                fb[fa[i]] = str[i]-'0';
            for(i = 1, k = 1; i <= n; i++) {
                if(fb[i])
                    k = k<<1|1;
                else
                    k = k<<1;
            }
            putchar(f[k-(1<<n)]);
        }
        puts("\n");
    }
    return 0;
}
