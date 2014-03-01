#include <stdio.h>
#include <string.h>
int idx;
char map[33][33];
char tree[3024];
void color(int x, int y, int b2) {
    char c = tree[idx];
     if(c == 'p') {
        idx++;
        color(x, y+b2/2, b2/2);
        color(x, y, b2/2);
        color(x+b2/2, y, b2/2);
        color(x+b2/2, y+b2/2, b2/2);
    } else if(c == 'f') {
        int i, j;
        for(i = x; i < x+b2; i++) {
            for(j = y; j < y+b2; j++) {
                map[i][j] = 1;
            }
        }
        idx++;
    } else
        idx++;
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    getchar();
    while(t--) {
        memset(map, 0, sizeof(map));
        scanf("%s", tree);
        idx = 0;
        color(0, 0, 32);
        scanf("%s", tree);
        idx = 0;
        color(0, 0, 32);
        int ans = 0;
        for(i = 0; i < 32; i++)
            for(j = 0; j < 32; j++)
                ans += map[i][j];
        printf("There are %d black pixels.\n", ans);
    }
    return 0;
}
