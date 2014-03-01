#include <stdio.h>

char word[1005][1005];
int main() {
    int n, m, i, j;
    int idx[1005];
    while(scanf("%d %d", &n, &m) == 2) {
        while(getchar() != '\n');
        gets(word[0]);
        idx[0] = 0;
        for(i = 1; i < n; i++) {
            int cnt = 0;
            gets(word[i]);
            for(j = 0; j < m; j++)
                if(word[i][j] != word[0][j])
                    cnt++;
            idx[cnt] = i;
        }
        for(i = 0; i < n; i++)
            puts(word[idx[i]]);
    }
    return 0;
}
/*
6 5
remar
pitos
remas
remos
retos
ritos
5 4
pato
lisa
pata
pita
pisa
*/
