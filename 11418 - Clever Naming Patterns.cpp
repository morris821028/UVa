#include <stdio.h>
#include <string.h>
#define toupper(x) (x >= 'a' ? x-'a'+'A' : x)
#define tolower(x) (x >= 'a' ? x : x-'A'+'a')
int g[100][100], gt[100];
int mx[100], my[100], used[100];
int dfs(int x) {
    int i, y;
    for(i = 0; i < gt[x]; i++) {
        y = g[x][i];
        if(!used[y]) {
            used[y] = 1;
            if(my[y] == 0 || dfs(my[y])) {
                mx[x] = y, my[y] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    int test;
    scanf("%d", &test);
    int n, K[30], i, j, k, cases = 0;
    char word[30][30][100];
    while(test--) {
        scanf("%d", &n);
        memset(gt, 0, sizeof(gt));
        memset(mx, 0, sizeof(mx));
        memset(my, 0, sizeof(my));
        for(i = 1; i <= n; i++) {
            scanf("%d", &K[i]);
            for(j = 0; j < K[i]; j++) {
                scanf("%s", &word[i][j]);
                int x = i, y = 30+(word[i][j][0] >= 'a' ? word[i][j][0]-'a' : word[i][j][0]-'A');
                g[y][gt[y]++] = x;
                //printf("%d %d\n", i, g[i][gt[i]]);
            }
        }
        int ans = 0;
        for(i = 30; i < 30+n; i++) {
            if(!mx[i]) {
                memset(used, 0, sizeof(used));
                if(dfs(i))
                    ans++;
            }
        }
        printf("Case #%d:\n", ++cases);
        for(i = 30; i < 30+n; i++) {
            for(j = 0; j < K[mx[i]]; j++) {
                if(tolower(word[mx[i]][j][0]) == i-30+'a') {
                    printf("%c", toupper(word[mx[i]][j][0]));
                    for(k = 1; word[mx[i]][j][k]; k++)
                        printf("%c", tolower(word[mx[i]][j][k]));
                    puts("");
                    break;
                }
            }
        }
    }
    return 0;
}
/*
4
3
2 Apples Oranges
1 Bananas
5 Apricots Blueberries Cranberries Zuccini Yams
1
1 ApPlEs
2
2 a b
1 axe
4
4 Aa Ba Ca Da
3 Ab Bb Cb
2 Ac Bc
1 Ad
*/
