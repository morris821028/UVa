#include <stdio.h>
#include <string.h>
char g[10][3][5] = {
    {" _ ", "| |", "|_|"},
    {"   ", "  |", "  |"},
    {" _ ", " _|", "|_ "},
    {" _ ", " _|", " _|"},
    {"   ", "|_|", "  |"},
    {" _ ", "|_ ", " _|"},
    {" _ ", "|_ ", "|_|"},
    {" _ ", "  |", "  |"},
    {" _ ", "|_|", "|_|"},
    {" _ ", "|_|", " _|"}
};
int gp[9][10], tr[9], user[9];
long long rescnt, res;
void dfs(int idx, int f) {
    int i;
    if(rescnt >= 2)    return;
    if(idx == 10) {
        int code = 0;
        for(i = 0; i < 9; i++)
            code += (9-i)*user[i];
        if(code%11) return;
        int tmp = 0;
        for(i = 0; i < 9; i++)
            tmp = tmp*10 + user[i];
        rescnt++;
        res = tmp;
        return;
    }
    if(f == 0) {
        for(i = 0; i <= 9; i++) {
            if(gp[idx][i]) {
                user[idx] = i;
                dfs(idx+1, 1);
            }
        }
    }
    if(tr[idx] >= 0) {
        user[idx] = tr[idx];
        dfs(idx+1, f);
    }
}
int main() {
    int i, j, k, l;
    char s[3][30];
    gets(s[0]);
    while(gets(s[0])) {
        gets(s[1]);
        gets(s[2]);
        memset(gp, 0, sizeof(gp));
        memset(tr, -1, sizeof(tr));
        for(i = 0; s[0][i]; i += 3) {
            for(j = 0; j <= 9; j++) {
                int err = 0, cor = 1;
                for(k = 0; k < 3; k++) {
                    for(l = 0; l < 3; l++) {
                        if(s[k][i+l] != ' ' &&
                           g[j][k][l] == ' ')
                           err = 1;
                        cor &= (s[k][i+l] == g[j][k][l]);
                    }
                }
                if(!err)
                    gp[i/3][j] = 1;
                if(cor)
                    tr[i/3] = j;
            }
        }
        int code = 0;
        for(i = 0; i < 9; i++) {
            if(tr[i] < 0)   code = -1, i = 20;
            else
                code += (9-i)*tr[i];
        }
        if(code%11 == 0) {
            for(i = 0; i < 9; i++)
                putchar(tr[i]+'0');
            puts("");
            continue;
        }
        if(i == 9) {
            puts("failure");
            continue;
        }
        rescnt = 0, res = -1;
        dfs(0, 0);
        if(rescnt == 0)
            puts("failure");
        else if(rescnt == 2)
            puts("ambiguous");
        else
            printf("%lld\n", res);
    }
    return 0;
}
/*
5
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
    _  _     _  _  _  _
  | _| _||_||_ |_   ||_|  |
  ||_  _|  | _||_|  ||_|  |
    _  _  _  _  _  _     _
|_||_|| || ||_   |  |  || |
  | _||_||_||_|  |  |  | _|
 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|
 _  _  _  _  _  _  _  _  _
|_|   |_||_||_||_||_||_||_|
|_|  ||_||_||_||_||_||_||_|
*/
