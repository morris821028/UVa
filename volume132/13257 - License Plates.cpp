#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int MAXN = 100005;
static const int MAXC = 26;
static char s[MAXN];
static int pos[MAXN][MAXC];
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s", s);
        int n = (int) strlen(s);
        for (int i = 0; i < MAXC; i++)
            pos[n][i] = n;
        for (int i = n-1; i >= 0; i--) {
            memcpy(pos[i], pos[i+1], sizeof(pos[0]));
            int x = s[i]-'A';
            pos[i][x] = i;
        }
        
        int ret = 0;
        for (int c = 0; c < 26; c++) {
            if (pos[0][c] == n)
                continue;
            int x = pos[0][c];
            for (int a = 0; a < 26; a++) {
                if (pos[x+1][a] == n)
                    continue;
                int y = pos[x+1][a];
                for (int b = 0; b < 26; b++) {
                    if (pos[y+1][b] == n)
                        continue;
                    ret++;
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 5
 PROGRAMMING
 COLOMBIA
 NUEVE
 AAAAAAA
 PQ
*/

