#include <stdio.h>
#include <map>
#include <queue>
#include <iostream>
#define hash_r 100003
using namespace std;
struct edge {
    int to;
    char v1, v2;
};
map<int, edge> R[hash_r];
void insert(int state, edge& s) {
    R[state%hash_r][state] = s;
}
int find(int state) {
    return R[state%hash_r].find(state) != R[state%hash_r].end();
}
void init_bfs() {
    edge E;
    E.to = -1;
    insert(123456789, E);
    int i, j, k, state, tn, tmp;
    int board[3][3];
    char v;
    queue<int> Q;
    Q.push(123456789);
    while(!Q.empty()) {
        state = tn = Q.front();
        Q.pop();
        for(i = 2; i >= 0; i--) {
            for(j = 2; j >= 0; j--) {
                board[i][j] = tn%10;
                tn /= 10;
            }
        }
        /*for(i = 0; i < 3; i++, puts(""))
            for(j = 0; j < 3; j++)
                printf("%d", board[i][j]);
        printf("--");
        getchar();*/
        for(i = 0; i < 3; i++) {
            tn = board[i][0];
            for(j = 1; j < 3; j++)
                board[i][j-1] = board[i][j];
            board[i][2] = tn;
           // printf("H%d\n", tn);
            tmp = 0;
            for(j = 0; j < 3; j++)
                for(k = 0; k < 3; k++)
                    tmp = tmp*10 + board[j][k];
            if(!find(tmp)) {
                E.to = state;
                E.v1 = 'H', E.v2 = i+1+'0';
                insert(tmp, E);
                Q.push(tmp);
            }
            tn = board[i][2];
            for(j = 1; j >= 0; j--)
                board[i][j+1] = board[i][j];
            board[i][0] = tn;
        }
        for(i = 0; i < 3; i++) {
            tn = board[2][i];
            for(j = 1; j >= 0; j--)
                board[j+1][i] = board[j][i];
            board[0][i] = tn;
           // printf("V%d\n", tn);
            tmp = 0;
            for(j = 0; j < 3; j++)
                for(k = 0; k < 3; k++)
                    tmp = tmp*10 + board[j][k];
            if(!find(tmp)) {
                E.to = state;
                E.v1 = 'V', E.v2 = i+1+'0';
                insert(tmp, E);
                Q.push(tmp);
            }
            tn = board[0][i];
            for(j = 1; j < 3; j++)
                board[j-1][i] = board[j][i];
            board[2][i] = tn;
        }
    }
}
char way[250];
int len;
void back(int state) {
    if(state == 123456789)  return;
    edge E = R[state%hash_r][state];
    way[len++] = E.v1;
    way[len++] = E.v2;
    back(E.to);
}
int main() {
    init_bfs();
    while(1) {
        int x, i, state = 0;
        for(i = 0; i < 9; i++) {
            if(scanf("%d", &x) != 1)
                return 0;
            state = state *10 + x;
        }
        if(!find(state))
            puts("Not solvable");
        else {
            len = 0, back(state);
            way[len] = '\0';
            if(len)
                printf("%d %s\n", len/2, way);
            else
                puts("0");
        }
    }
    return 0;
}
