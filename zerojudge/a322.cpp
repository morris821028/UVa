#include <stdio.h>
#include <string.h>
int g1[27][27] = {}, g2[27][27];
int c1[27], c2[27], used[27], way[27];
int N, M, flag = 0;
void dfs(int idx) {
    if(flag)    return;
    if(idx == N) {
        int i, j;
        for(i = 0; i < 26; i++)
            for(j = 0; j < 26; j++)
                if(g1[i][j] && g1[i][j] != g2[way[i]][way[j]])
                    return;
        flag = 1;
    }
    int i;
    for(i = 0; i < N; i++) {
        if(used[i] == 0) {
            used[i] = 1;
            way[c1[idx]] = c2[i];
            dfs(idx+1);
            used[i] = 0;
        }
    }
}
int main() {
    int t, i;
    char a[10], b[10];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &N, &M);
        memset(g1, 0, sizeof(g1));
        memset(g2, 0, sizeof(g2));
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        for(i = 0; i < M; i++) {
            scanf("%s %s", a, b);
            g1[a[0]-'A'][b[0]-'A'] = 1;
            g1[b[0]-'A'][a[0]-'A'] = 1;
            c1[a[0]-'A'] = c1[b[0]-'A'] = 1;
        }
        for(i = 0; i < M; i++) {
            scanf("%s %s", a, b);
            g2[a[0]-'a'][b[0]-'a'] = 1;
            g2[b[0]-'a'][a[0]-'a'] = 1;
            c2[a[0]-'a'] = c2[b[0]-'a'] = 1;
        }
        flag = 0;
        int idx;
        for(i = 0, idx = 0; i < 26; i++)
            if(c1[i])
                c1[idx++] = i;
        for(i = 0, idx = 0; i < 26; i++)
            if(c2[i])
                c2[idx++] = i;
        dfs(0);
        puts(flag ? "yes" : "no");
    }
    return 0;
}
