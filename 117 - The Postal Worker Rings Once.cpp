#include <stdio.h>
#include <string.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
int main() {
    char road[50];
    while(scanf("%s", road) == 1) {
        int map[26][26] = {}, i, j, k;
        int deg[26] = {}, slen, sum = 0;
        memset(map, 63, sizeof(map));
        slen = strlen(road);
        i = road[0]-'a', j = road[slen-1]-'a';
        map[i][j] = min(slen, map[i][j]);
        map[j][i] = min(slen, map[j][i]);
        deg[i]++, deg[j]++;
        sum += slen;
        while(scanf("%s", road) == 1) {
            if(!strcmp("deadend", road))
                break;
            slen = strlen(road);
            i = road[0]-'a', j = road[slen-1]-'a';
            map[i][j] = min(slen, map[i][j]);
            map[j][i] = min(slen, map[j][i]);
            deg[i]++, deg[j]++;
            sum += slen;
        }
        int idx = 0, odeg[2];
        for(i = 0; i < 26; i++)
            if(deg[i]&1)
                odeg[idx++] = i;
        if(idx) {
            for(k = 0; k < 26; k++)
                for(i = 0; i < 26; i++)
                    for(j = 0; j < 26; j++)
                        map[i][j] = min(map[i][j], map[i][k]+map[k][j]);
            sum += map[odeg[0]][odeg[1]];
        }
        printf("%d\n", sum);
    }
    return 0;
}
