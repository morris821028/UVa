#include <stdio.h>
#define toLower(c) ((c >= 'A' && c <= 'Z') ? (c-'A'+'a') : (c))
int t, n, m, i, j, k;
void find(char str[], char map[][60]) {
    static int D[][2] = {{0,1},{1,0},{-1,0},{0,-1},
                        {1,1},{1,-1},{-1,1},{-1,-1}};
    int i, j, k, x, y, idx;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            for(k = 0; k < 8; k++) {
                x = i, y = j, idx = 0;
                while(map[x][y] == str[idx]) {
                    x += D[k][0], y += D[k][1];
                    idx++;
                    if(str[idx] == '\0') {
                        printf("%d %d\n", i+1, j+1);
                        return;
                    }
                    if(x < 0 || y < 0 || x >= n || y >= m)
                        break;
                }
            }
        }
    }
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        char map[60][60], str[60];
        for(i = 0; i < n; i++) {
            scanf("%s", &map[i]);
            for(j = 0; j < m; j++)
                map[i][j] = toLower(map[i][j]);
        }
        scanf("%d", &k);
        while(k--) {
            scanf("%s", str);
            for(i = 0; str[i]; i++)
                str[i] = toLower(str[i]);
            find(str, map);
        }
        if(t)
            puts("");
    }
    return 0;
}
