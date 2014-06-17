#include <stdio.h>
#include <string.h>
int p[100000] = {};
int head[100000] = {};
void sieve() {
    int i, j, k;
    int cnt = 0;
    for(i = 2; i < 100000; i++) {
        if(p[i] == 0) {
            for(j = i+i; j < 100000; j += i)
                p[j] = 1;
            if(i > 10000) {
                cnt++;
                k = i;
                while(k) {
                    head[k] = 1;
                    k /= 10;
                }
            }
        }
    }
    printf("%d\n", cnt);
}
char g[20][20];
int firstline = 0;
void dfs(int x, int y, int k, int sum) {
    if(g[0][0]+g[1][1]+g[2][2]+g[3][3]+g[4][4]-5*'0' > sum)
        return;
    if(g[0][4]+g[1][3]+g[2][2]+g[3][1]+g[4][0]-5*'0' > sum)
        return;
    if(x == 4 && y == 1 && g[0][4]+g[1][3]+g[2][2]+g[3][1]+g[4][0]-5*'0' != sum)
        return;
    if(x == 5 && y == 0 && g[0][0]+g[1][1]+g[2][2]+g[3][3]+g[4][4]-5*'0' != sum)
        return;
    if(y == 5) {
        g[x][y] = '\0';
        if(sum == k)
            dfs(x+1, 0, 0, sum);
        return;
    }
    if(x == 5) {
        int i;
        if(firstline)   puts("");
        firstline = 1;
        for(i = 0; i < 5; i++)
            puts(g[i]);
        return;
    }
    int i, j, st, tmp;
    if(x == 0 || y == 0)    st = '1';
    else    st = '0';
    for(i = st; i <= '9' && k+i-'0' <= sum; i++) {
        tmp = 0;
        g[x][y] = i;
        for(j = 0; j <= x; j++) // check column sum
            tmp += g[j][y]-'0';
        if(tmp > sum)   {g[x][y] = '0';continue;}
        tmp = 0;
        for(j = 0; j <= x; j++) // check column head prime possible
            tmp = tmp*10 + g[j][y]-'0';
        if(!head[tmp])  {g[x][y] = '0';continue;}
        tmp = 0;
        for(j = 0; j <= y; j++) // check row head prime possible
            tmp = tmp*10 + g[x][j]-'0';
        if(!head[tmp])  {g[x][y] = '0';continue;}
        if(x == y) { // check diagonal head prime possible
            tmp = 0;
            for(j = 0; j <= y; j++)
                tmp = tmp*10 + g[j][j]-'0';
            if(!head[tmp])  {g[x][y] = '0';continue;}
        }
        if(x == 4 && y == 0) { // check diagonal head prime possible
            tmp = 0;
            for(j = 0; j < 5; j++)
                tmp = tmp*10 + g[4-j][j]-'0';
            if(!head[tmp])  {g[x][y] = '0';continue;}
        }
        dfs(x, y+1, k+i-'0', sum);
        g[x][y] = '0';
    }
}
int main() {
    sieve();
    int t, sum, d;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &sum, &d);
        memset(g, '0', sizeof(g));
        g[0][0] = d+'0';
        firstline = 0;
        dfs(0, 1, d, sum);
        if(t)   puts("");
    }
    return 0;
}
