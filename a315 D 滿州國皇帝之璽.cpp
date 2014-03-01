#include <stdio.h>

int main() {
    int t, n, m, p, x, y, r;
    int i, j, k, a, b;
    char G[105][105], A[105][105];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &p);
        for(i = 0; i < m; i++)
            scanf("%s", G[i]);
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                A[i][j] = '.';
        while(p--) {
            scanf("%d %d %d", &x, &y, &r);
            if(r == 0) {
                for(i = 0; i < m; i++)
                    for(j = 0; j < m; j++)
                        if(x+i >= 0 && x+i < n && y+j >= 0 && y+j < n) {
                            if(G[i][j] == '#')
                                A[x+i][y+j] = '#';
                        }
            } else if(r == 1) {
                for(j = 0, a = 0; j < m; j++, a++)
                    for(i = m-1, b = 0; i >= 0; i--, b++)
                        if(x+a >= 0 && x+a < n && y+b >= 0 && y+b < n)
                            if(G[i][j] == '#')
                                A[x+a][y+b] = '#';
            } else if(r == 2) {
                for(i = m-1, a = 0; i >= 0; i--, a++)
                    for(j = m-1, b = 0; j >= 0; j--, b++)
                        if(x+a >= 0 && x+a < n && y+b >= 0 && y+b < n)
                            if(G[i][j] == '#')
                                A[x+a][y+b] = '#';
            } else {
                for(j = m-1, a = 0; j >= 0; j--, a++)
                    for(i = 0, b = 0; i < m; i++, b++)
                        if(x+a >= 0 && x+a < n && y+b >= 0 && y+b < n)
                            if(G[i][j] == '#')
                                A[x+a][y+b] = '#';
            }
        }
        for(i = 0; i < n; i++, puts(""))
            for(j = 0; j < n; j++)
                putchar(A[i][j]);
    }
    return 0;
}
/*
3
5 3 2
.##
.#.
##.
0 2 1
2 0 0
3 5 3
###.#
..#.#
#####
#.#..
#.###
-2 -2 0
-1 -2 2
-1 -1 1
5 4 0
....
....
....
....
*/
