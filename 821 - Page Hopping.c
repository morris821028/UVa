#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))

int node(int mark[], int *size, int *v) {
    if(mark[*v] == 0)
        mark[*v] = ++(*size);
    return mark[*v];
}
int main() {
    int x, y, Case = 0, i, j, k, m;
    int map[101][101], in[100000][2];
    while(scanf("%d %d", &x, &y) == 2) {
        if(x == 0 && y == 0)
            break;
        int mark[101] = {}, size = 0;
        m = 0;
        x = node(mark, &size, &x);
        y = node(mark, &size, &y);
        in[m][0] = x, in[m][1] = y;
        m++;
        while(scanf("%d %d", &x, &y) == 2) {
            if(x == 0 && y == 0)
                break;
            x = node(mark, &size, &x);
            y = node(mark, &size, &y);
            in[m][0] = x, in[m][1] = y;
            m++;
        }
        for(i = 1; i <= size; i++)
            for(j = 1; j <= size; j++)
                map[i][j] = 10000;
        for(i = 0; i < m; i++)
            map[in[i][0]][in[i][1]] = 1;
        for(k = 1; k <= size; k++)
            for(i = 1; i <= size; i++)
                for(j = 1; j <= size; j++)
                    map[i][j] = min(map[i][j], map[i][k]+map[k][j]);
        int sum = 0;
        for(i = 1; i <= size; i++) {
            for(j = 1; j <= size; j++) {
                if(i != j)
                    sum += map[i][j];
            }
        }
        printf("Case %d: average length between pages = %.3lf clicks\n", ++Case, (double)sum/size/(size-1));
    }
    return 0;
}
