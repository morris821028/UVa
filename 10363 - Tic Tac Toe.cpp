#include <stdio.h>
int check(char g[][4]) {
    int i, j, o = 0, x = 0;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(g[i][j] == 'O')
                o++;
            else if(g[i][j] == 'X')
                x++;
    if(!(x == o || x == o+1))
        return 0;
    int oflag = 0, xflag = 0;
    for(i = 0; i < 3; i++) {
        if(g[i][0] == 'O' && g[i][0] == g[i][1] && g[i][1] == g[i][2])
            oflag = 1;
        if(g[0][i] == 'O' && g[0][i] == g[1][i] && g[1][i] == g[2][i])
            oflag = 1;
        if(g[i][0] == 'X' && g[i][0] == g[i][1] && g[i][1] == g[i][2])
            xflag = 1;
        if(g[0][i] == 'X' && g[0][i] == g[1][i] && g[1][i] == g[2][i])
            xflag = 1;
    }
    if(g[0][0] == 'O' && g[0][0] == g[1][1] && g[1][1] == g[2][2])
        oflag = 1;
    if(g[2][0] == 'O' && g[2][0] == g[1][1] && g[1][1] == g[0][2])
        oflag = 1;
    if(g[0][0] == 'X' && g[0][0] == g[1][1] && g[1][1] == g[2][2])
        xflag = 1;
    if(g[2][0] == 'X' && g[2][0] == g[1][1] && g[1][1] == g[0][2])
        xflag = 1;
    if(oflag && xflag)
        return 0;
    if(!oflag && !xflag)
        return 1;
    if(xflag && x == o+1)
        return 1;
    if(oflag && x == o)
        return 1;
    return 0;
}
int main() {
    int t;
    char g[4][4];
    scanf("%d", &t);
    while(t--) {
        scanf("%s%s%s", g[0], g[1], g[2]);
        if(check(g))
            puts("yes");
        else
            puts("no");
    }
    return 0;
}
