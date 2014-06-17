#include <stdio.h>
char word[105][1024], exp[1024];
void dfs(int idx, int p) {
    if(exp[p] == '\0') {
        int i;
        for(i = 0; exp[i]; i++) {
            if(exp[i] == '#')
                printf("%s", word[idx]);
            else
                putchar(exp[i]);
        }
        puts("");
        return;
    }
    if(exp[p] == '#')   dfs(idx, p+1);
    else {
        int i;
        for(i = '0'; i <= '9'; i++) {
            exp[p] = i;
            dfs(idx, p+1);
        }
    }
}
int main() {
    int n, m, i;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%s", word[i]);
        scanf("%d", &m);
        puts("--");
        while(m--) {
            scanf("%s", exp);
            for(i = 0; i < n; i++)
                dfs(i, 0);
        }
    }
    return 0;
}
