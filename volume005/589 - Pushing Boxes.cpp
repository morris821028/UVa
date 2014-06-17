#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
int used[25][25][25][25] = {};
int step[25][25][25][25] = {};
struct Node {
    int x, y, a, b, v;
    Node(int a1, int a2, int a3, int a4, int a5) {
        x = a1, y = a2;
        a = a3, b = a4;
        v = a5;
    }
};
struct cmp {
    bool operator() (Node a, Node b) {
        return a.v > b.v;
    }
};
void print(int x, int y, int a, int b) {
    //printf("%d %d %d %d %d\n", x, y, a, b, used[x][y][a][b]);
    if(used[x][y][a][b] == 1)
        return;
    static int dirx[4] = {1,0,0,-1};
    static int diry[4] = {0,-1,1,0}; // NEWS/news
    static char chd[4] = {'N','E','W','S'};
    int i = 0;
    for(i = 0; i < 4; i++) {
        if(step[x][y][a][b] == chd[i]) {
            print(x+dirx[i], y+diry[i], a+dirx[i], b+diry[i]);
        }
        if(step[x][y][a][b] == chd[i]+32) {
            print(x+dirx[i], y+diry[i], a, b);
        }
    }
    putchar(step[x][y][a][b]);
}
int main() {
    int n, m, i, j, k;
    int cases = 0;
    char g[25][25];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)
            break;
        printf("Maze #%d\n", ++cases);
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        memset(used, 0, sizeof(used));
        int bx, by, sx, sy;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(g[i][j] == 'B')
                    bx = i, by = j;
                if(g[i][j] == 'S')
                    sx = i, sy = j;
            }
        }
        used[sx][sy][bx][by] = 1;
        priority_queue<Node, vector<Node>, cmp> Q;
        Q.push(Node(sx, sy, bx, by, 1));
        Node tn(0,0,0,0,0);
        int tx, ty;
        int dirx[4] = {-1,0,0,1};
        int diry[4] = {0,1,-1,0}; // NEWS/news
        char chd[4] = {'N','E','W','S'};
        int sol = 0;
        while(!Q.empty()) {
            tn = Q.top(), Q.pop();
            //printf("%d %d %d %d %c\n", tn.x, tn.y, tn.a, tn.b, step[tn.x][tn.y][tn.a][tn.b]);
            //printf("%d\n", step[tn.x][tn.y][tn.a][tn.b]);
            if(g[tn.a][tn.b] == 'T') {
                print(tn.x, tn.y, tn.a, tn.b);
                puts("");
                sol = 1;
                break;
            }
            for(i = 0; i < 4; i++) {// NEWS
                if(tn.a == tn.x+dirx[i] && tn.b == tn.y+diry[i]) {
                    tx = tn.a+dirx[i], ty = tn.b+diry[i];
                    if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                        continue;
                    if(g[tx][ty] == '#')    continue;
                    int *p = &used[tn.x+dirx[i]][tn.y+diry[i]][tn.a+dirx[i]][tn.b+diry[i]];
                    if(*p <= used[tn.x][tn.y][tn.a][tn.b]+100000 && *p)  continue;
                    *p = used[tn.x][tn.y][tn.a][tn.b]+100000;
                    step[tn.x+dirx[i]][tn.y+diry[i]][tn.a+dirx[i]][tn.b+diry[i]] = chd[i];
                    Q.push(Node(tn.x+dirx[i], tn.y+diry[i], tn.a+dirx[i], tn.b+diry[i], used[tn.x][tn.y][tn.a][tn.b]+100000));
                }
            }
            for(i = 0; i < 4; i++) {//news
                if(tn.a == tn.x+dirx[i] && tn.b == tn.y+diry[i])
                    continue;
                tx = tn.x+dirx[i], ty = tn.y+diry[i];
                if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                    continue;
                if(g[tx][ty] == '#')    continue;
                int *p = &used[tn.x+dirx[i]][tn.y+diry[i]][tn.a][tn.b];
                if(*p <= used[tn.x][tn.y][tn.a][tn.b]+1 && *p)  continue;
                *p = used[tn.x][tn.y][tn.a][tn.b]+1;
                step[tn.x+dirx[i]][tn.y+diry[i]][tn.a][tn.b] = chd[i]+32;
                Q.push(Node(tn.x+dirx[i], tn.y+diry[i], tn.a, tn.b, used[tn.x][tn.y][tn.a][tn.b]+1));
            }
        }
        if(!sol)
            puts("Impossible.");
        puts("");
    }
    return 0;
}
