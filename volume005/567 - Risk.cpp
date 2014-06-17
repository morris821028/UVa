#include <stdio.h>

int main() {
    int i, j, k, test = 0;
    int n;
    while(scanf("%d", &n) == 1) {
        int map[21][21] = {};
        for(i = 1; i <= 19; i++) {
            if(i != 1)
                scanf("%d", &n);
            while(n--) {
                scanf("%d", &k);
                map[i][k] = 1;
                map[k][i] = 1;
            }
        }
        for(k = 1; k <= 20; k++) {
            for(i = 1; i <= 20; i++) {
                for(j = 1; j <= 20; j++) {
                    if(map[i][j] == 0 || map[i][j] > map[i][k]+map[k][j]) {
                        if(map[i][k] && map[k][j])
                            map[i][j] = map[i][k] + map[k][j];
                    }
                }
            }
        }
        scanf("%d", &n);
        printf("Test Set #%d\n", ++test);
        while(n--) {
            scanf("%d %d", &i, &j);
            printf("%2d to %2d: %d\n", i, j, map[i][j]);
        }
        puts("");
    }
    return 0;
}
