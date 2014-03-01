#include <stdio.h>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
#define hash_r 131071
using namespace std;
map<int, string> R[hash_r];
void insert(int state, string& s) {
    R[state%hash_r][state] = s;
}
int find(int state) {
    return R[state%hash_r].find(state) != R[state%hash_r].end();
}
void build_bfs() {
    string step = "";
    int i, j, k, board[3][3];
    int tn, state, ix, iy;
    int tx, ty;
    int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    char dirc[4] = {'l', 'r', 'u', 'd'};
    insert(123456789, step);
    queue<int> Q;
    Q.push(123456789);
    int cnt = 0;
    while(!Q.empty()) {
        cnt++;
        tn = state = Q.front();

        Q.pop();
        for(i = 2; i >= 0; i--) {
            for(j = 2; j >= 0; j--) {
                board[i][j] = tn%10, tn /= 10;
                if(board[i][j] == 9)
                    ix = i, iy = j;
            }
        }/*
        for(i = 0; i < 3; i ++, puts(""))
            for(j = 0; j < 3; j++)
                printf("%d", board[i][j]);
        cout << R[state%hash_r][state] << endl;*/
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
                step = dirc[i] + R[state%hash_r][state];
                //cout << tn << " " << step << endl;
                insert(tn, step);
                Q.push(tn);
            }
            swap(board[ix][iy], board[tx][ty]);
        }
        //getchar();
    }
    //printf("%d\n", cnt);
}
int main() {
    build_bfs();
    int t, i, x, state;
    char s[2];
    scanf("%d", &t);
    while(t--) {
        state = 0;
        for(i = 0; i < 9; i++) {
            scanf("%s", s);
            if(s[0] == 'x')
                x = 9;
            else
                x = s[0]-'0';
            state = state*10 + x;
        }
        if(find(state))
            cout << R[state%hash_r][state] << endl;
        else
            cout << "unsolvable" << endl;
        if(t)
            cout << endl;
    }
    return 0;
}
/*
luurrdldruuldrdlurd
ullddrurdllurdruldr
*/
