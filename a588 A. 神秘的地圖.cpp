#include <stdio.h>
#include <string.h>
int g1[20][20], g2[20][20];
int n1, n2, m1, m2;
int used[20] = {}, mapped[20] = {};
int flag = 0;
void dfs(int idx) {
    if(flag)    return;
    if(idx == n2) {
        int i, j;
        for(i = 0; i < n2; i++)
            for(j = 0; j < n2; j++)
                if(g2[i][j] != g1[mapped[i]][mapped[j]])
                    return;
        flag = 1;
        return;
    }
    int i, j;
    for(i = 0; i < n1; i++) {
        if(used[i] == 0) {
            used[i] = 1;
            mapped[idx] = i;
            for(j = 0; j < idx; j++)
                if(g1[mapped[idx]][mapped[j]] != g2[idx][j])
                    break;
            if(j == idx)
                dfs(idx+1);
            used[i] = 0;
        }
    }
}
int main() {
    int t, i, x, y;
    scanf("%d", &t);
    while(t--) {
        memset(g1, 0, sizeof(g1));
        memset(g2, 0, sizeof(g2));
        scanf("%d %d", &n1, &m1);
        while(m1--) {
            scanf("%d %d", &x, &y);
            g1[x][y]++, g1[y][x]++;
        }
        scanf("%d %d", &n2, &m2);
        while(m2--) {
            scanf("%d %d", &x, &y);
            g2[x][y]++, g2[y][x]++;
        }
        if(n2 > n1) {
            puts("NO");
            continue;
        }
        flag = 0;
        dfs(0);
        if(flag)    puts("YES");
        else        puts("NO");
    }
    return 0;
}
