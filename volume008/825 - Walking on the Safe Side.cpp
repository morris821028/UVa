#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    int t, n, m, x, y;
    string line;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        int map[101][101] = {}, i, j;
        map[0][1] = 1;
        getchar();
        for(i = 1; i <= n; i++) {
            getline(cin, line);
            stringstream sin(line);
            sin >> x;
            while(sin >> y) {
                map[x][y] = -1;
            }
        }
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                if(map[i][j] == -1)
                    continue;
                if(map[i][j-1] != -1)
                    map[i][j] += map[i][j-1];
                if(map[i-1][j] != -1)
                    map[i][j] += map[i-1][j];
            }
        }
        printf("%d\n", map[n][m]);
        if(t)
            puts("");
    }
    return 0;
}
