#include <stdio.h>
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
char g[100][100], star[100][100];
int idx;
void paintstar(int i, int j) {
    if(i < 0 || j < 0 || i >= idx || j > 99)  return;
    if(!(g[i][j] == ' ' || g[i][j] == '\0'))
        return;
    if(star[i][j])  return;
    star[i][j] = 1;
    paintstar(i+1, j);
    paintstar(i-1, j);
    paintstar(i, j+1);
    paintstar(i, j-1);
}
void paint(int i, int j) {
    if(i < 0 || j < 0 || i >= idx || j > 99)  return;
    if(star[i][j]) {
        if(g[i][j] == '\0') {
            int tmp = j;
            while(tmp >= 0 && g[i][tmp] == '\0')
                tmp--;
            tmp++;
            while(tmp < j)
                g[i][tmp] = ' ', tmp++;
            g[i][j+1] = '\0';
        }
        g[i][j] = '#';
    }
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    cin.ignore(100, '\n');
    while(t--) {
        memset(g, 0, sizeof(g));
        memset(star, 0, sizeof(star));
        idx = 0;
        while(gets(g[idx])) {
            if(g[idx][0] == '_')
                break;
            idx++;
        }
        for(i = 0; i < idx; i++)
            for(j = 0; g[i][j]; j++)
                if(g[i][j] == '*') {
                    g[i][j] = ' ';
                    paintstar(i, j);
                }
        for(i = 0; i < idx; i++) {
            for(j = 0; g[i][j]; j++) {
                if(g[i][j] != ' ' && g[i][j] != '#') {
                    paint(i+1, j);
                    paint(i-1, j);
                    paint(i, j+1);
                    paint(i, j-1);
                }
            }
        }
        for(i = 0; i <= idx; i++) {
            j = strlen(g[i])-1;
            while(j >= 0 && g[i][j] == ' ')
                j--;
            g[i][j+1] = '\0';
            puts(g[i]);
        }
    }
    return 0;
}
