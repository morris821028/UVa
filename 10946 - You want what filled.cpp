#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int v;
    char c;
} Out;
int cmp(const void *i, const void *j) {
    Out *a, *b;
    a = (Out *)i, b = (Out *)j;
    if(a->v != b->v)
        return b->v - a->v;
    return a->c - b->c;
}
int main() {
    int n, m, test = 0, i, j, k, l;
    char map[51][51];
    Out ans[2500];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        for(i = 0; i < n; i++)
            scanf("%s", map[i]);
        int used[51][51] = {}, D[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        int Q[2500][2], Qt, idx = 0, x, y, xx, yy;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(used[i][j] == 0 && map[i][j] != '.') {
                    Qt = 0, Q[0][0] = i, Q[0][1] = j, used[i][j] = 1;
                    for(k = 0; k <= Qt; k++) {
                        x = Q[k][0], y = Q[k][1];
                        for(l = 0; l < 4; l++) {
                            xx = x+D[l][0], yy = y+D[l][1];
                            if(xx < 0 || yy < 0 || xx >= n || yy >= m)
                                continue;
                            if(used[xx][yy] == 0 && map[i][j] == map[xx][yy]) {
                                Qt++;
                                Q[Qt][0] = xx, Q[Qt][1] = yy;
                                used[xx][yy] = 1;
                            }
                        }
                    }
                    ans[idx].v = Qt+1, ans[idx].c = map[i][j];
                    idx++;
                }
            }
        }
        qsort(ans, idx, sizeof(Out), cmp);
        printf("Problem %d:\n", ++test);
        for(i = 0; i < idx; i++)
            printf("%c %d\n", ans[i].c, ans[i].v);
    }
    return 0;
}
