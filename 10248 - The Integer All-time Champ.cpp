#include <stdio.h>
#include <string.h>

int map[10][10] = {}, p = 0;
int indeg[10] = {}, outdeg[10] = {};
char ans[1000];
void dfs(int node) {
    int i;
    for(i = 0; i < 10; i++) {
        if(map[node][i]) {
            outdeg[node]--, indeg[i]--;
            map[node][i]--;
            dfs(i);
            ans[p] = i+'0', p++;
            break;
        }
    }
}
int main() {
    int n, m, i, j, x, y;
    while(scanf("%d %d", &n, &m) == 2) {
        memset(map, 0, sizeof(map));
        memset(indeg, 0, sizeof(indeg));
        memset(outdeg, 0, sizeof(outdeg));
        int need[10] = {};
        for(i = n; i <= m; i++) {
            if(i >= 10) {
                x = i/10, y = i%10;
                map[x][y]++;
                outdeg[x]++,  indeg[y]++;
            } else {
                need[i] = 1;
            }
        }
        int st = -1;
        for(i = 0; i < 10; i++) {
            while(indeg[i] > outdeg[i]) {
                for(j = 0; j < 10; j++) {
                    if(indeg[j] < outdeg[j]) {
                        outdeg[i]++, indeg[j]++;
                        map[i][j]++;
                        break;
                    }
                }
                if(j == 10)
                    break;
            }
            while(indeg[i] < outdeg[i]) {
                for(j = 0; j < 10; j++) {
                    if(indeg[j] > outdeg[j]) {
                        outdeg[j]++, indeg[i]++;
                        map[j][i]++;
                        break;
                    }
                }
                if(j == 10)
                    break;
            }
            if(indeg[i] != 0 || outdeg[i] != 0)
                st = i;
        }
        while(1) {
            int st = -1;
            for(i = 0; i < 10; i++)
                if(outdeg[i] > indeg[i])
                    st = i;
            if(st < 0) {
                for(i = 0; i < 10; i++)
                    if(outdeg[i] || indeg[i])
                        st = i;
            }
            if(st >= 0) {
                p = 0;
                dfs(st);
                ans[p] = st+'0';
                for(i = p; i >= 0; i--)
                    printf("%c", ans[i]), need[ans[i]-'0'] = 0;
                puts("");
            } else
                break;
        }
        for(i = 0; i < 10; i++)
            if(need[i])
                printf("%d", i);
        puts("");
    }
    return 0;
}/*
*/
