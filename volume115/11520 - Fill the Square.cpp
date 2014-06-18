#include <stdio.h>

int main() {
    int cases = 0;
    int t, n ,i, j, k, l;
    char map[20][20];
    scanf("%d", &t);
    while(t--) {
        printf("Case %d:\n", ++cases);
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%s", map[i]);
        int d[4][2]= {{0,1},{0,-1},{1,0},{-1,0}};
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(map[i][j] == '.') {
                    for(k = 'A'; k <= 'Z'; k++) {
                        map[i][j] = k;
                        for(l = 0; l < 4; l++) {
                            if(d[l][0]+i < 0 || d[l][0]+i >= n ||
                               d[l][1]+j < 0 || d[l][1]+j >= n)
                                continue;
                            if(map[i][j] == map[i+d[l][0]][j+d[l][1]])
                                break;
                        }
                        if(l == 4)  break;
                    }
                }
            }
        }
        for(i = 0; i < n; i++)
            puts(map[i]);
    }
    return 0;
}
