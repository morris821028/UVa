#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct card {
    char a, b;
};
bool cmp(card a, card b) {
    if(a.a != b.a) {
        if(a.a == 'C')  return true;
        if(b.a == 'C')  return false;
        if(a.a == 'D')  return true;
        if(b.a == 'D')  return false;
        if(a.a == 'S')  return true;
        if(b.a == 'S')  return false;
        if(a.a == 'H')  return true;
        if(b.a == 'H')  return false;
    }
    int x, y;
    switch(a.b) {
        case '0'...'9':x = a.b-'0';break;
        case 'A':x = 14;break;
        case 'T':x = 10;break;
        case 'J':x = 11;break;
        case 'Q':x = 12;break;
        case 'K':x = 13;break;
    }
    switch(b.b) {
        case '0'...'9':y = b.b-'0';break;
        case 'A':y = 14;break;
        case 'T':y = 10;break;
        case 'J':y = 11;break;
        case 'Q':y = 12;break;
        case 'K':y = 13;break;
    }
    return x < y;
}
int main() {
    char dir[50], cmd[500], F[] = "SWNE";
    int i, j;
    while(gets(dir) && dir[0] != '#') {
        int st;
        switch(dir[0]) {
            case 'N':st = 1;break;
            case 'E':st = 2;break;
            case 'S':st = 3;break;
            case 'W':st = 0;break;
        }
        card p[4][13];
        int pidx[4] = {};
        for(i = 0; i < 2; i++) {
            gets(cmd);
            int len = strlen(cmd);
            for(j = 0; j < len; j += 2) {
                p[st][pidx[st]].a = cmd[j];
                p[st][pidx[st]].b = cmd[j+1];
                pidx[st]++;
                st = (st+1)%4;
            }
        }
        for(i = 0; i < 4; i++) {
            printf("%c:", F[i]);
            int idx = (i+2)%4;
            sort(p[idx], p[idx]+13, cmp);
            for(j = 0; j < 13; j++)
                printf(" %c%c", p[idx][j].a, p[idx][j].b);
            puts("");
        }
    }
    return 0;
}
