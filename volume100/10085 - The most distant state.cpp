#include <stdio.h>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
#define hash_r 131071
using namespace std;
struct ele {
    char c;
    int f;
};
map<int, ele> R[hash_r];
void insert(int state, ele &s) {
    R[state%hash_r][state] = s;
}
int find(int state) {
    return R[state%hash_r].find(state) != R[state%hash_r].end();
}
void print(int state) {
    if(state) {
        ele e = R[state%hash_r][state];
        print(e.f);
        if(e.f)
            printf("%c", e.c);
    }
}
void build_bfs(int initState) {
    int i, j, k, board[3][3];
    int tn, state, ix, iy;
    int tx, ty;
    int dir[4][2] = {{-1, 0},{1,0},{0,-1},{0,1}};
    char dirc[4] = {'U', 'D', 'L', 'R'};
    ele e1, e2;
    e1.f = 0;
    insert(initState, e1);
    queue<int> Q;
    Q.push(initState);
    int cnt = 0;
    while(!Q.empty()) {
        cnt++;
        tn = state = Q.front();
        Q.pop();
        for(i = 2; i >= 0; i--) {
            for(j = 2; j >= 0; j--) {
                board[i][j] = tn%10, tn /= 10;
                if(board[i][j] == 0)
                    ix = i, iy = j;
            }
        }
        for(i = 0; i < 4; i++) {
            tx = ix+dir[i][0], ty = iy+dir[i][1];
            if(tx < 0 || ty < 0 || tx >= 3 || ty >= 3)
                continue;
            swap(board[ix][iy], board[tx][ty]);
            tn = 0;
            for(j = 0; j < 3; j++) {
                for(k = 0; k < 3; k++) {
                    tn = tn*10 + board[j][k];
                }
            }
            if(!find(tn)) {
                e1.c = dirc[i], e1.f = state;
                insert(tn, e1);
                Q.push(tn);
            }
            swap(board[ix][iy], board[tx][ty]);
        }
    }
    tn = state;
    for(i = 2; i >= 0; i--) {
        for(j = 2; j >= 0; j--) {
            board[i][j] = tn%10, tn /= 10;
        }
    }
    for(i = 0; i < 3; i ++, puts("")) {
        for(j = 0; j < 3; j++) {
            if(j)   putchar(' ');
            printf("%d", board[i][j]);
        }
    }
    print(state);
    puts("");
}
int main() {
    int t, i, x, state, cases = 0;
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < hash_r; i++)
            R[i].clear();
        state = 0;
        for(i = 0; i < 9; i++) {
            scanf("%d", &x);
            state = state*10 + x;
        }
        printf("Puzzle #%d\n", ++cases);
        build_bfs(state);
        puts("");
    }
    return 0;
}
/*
3
2 6 4
1 3 7
0 5 8

*/
