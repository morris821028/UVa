#include <stdio.h>
#include <string.h>
char putrank(char s) {
    switch(s) {
        case 10:return 'T';
        case 11:return 'J';
        case 12:return 'Q';
        case 13:return 'K';
        case 1:return 'A';
    }
    return s+'0';
}
int getrank(char s) {
    switch(s) {
        case 'T':return 10;
        case 'J':return 11;
        case 'Q':return 12;
        case 'K':return 13;
        case 'A':return 1;
    }
    return s-'0';
}
char putsuit(char s) {
    if(s == 0)    return 'C';
    if(s == 1)    return 'D';
    if(s == 2)    return 'H';
    if(s == 3)    return 'S';
}
int getsuit(char s) {
    if(s == 'C')    return 0;
    if(s == 'D')    return 1;
    if(s == 'H')    return 2;
    if(s == 'S')    return 3;
}
int main() {
    char in[10];
    while(1) {
        int r, s, i;
        int p[13][4], pt[13] = {};
        for(i = 51; i >= 0; i--) {
            scanf("%s", in);
            if(in[0] == '#')    return 0;
            r = getrank(in[0]);
            s = getsuit(in[1]);
            p[i%13][pt[i%13]++] = s*13+r;
           // printf("%d %d %d\n", r, s, s*13+r);
        }
        for(i = 0; i < 13; i++) {
            r = p[i][0], p[i][0] = p[i][3], p[i][3] = r;
            r = p[i][1], p[i][1] = p[i][2], p[i][2] = r;
        }
        int idx = 12, cnt = 0, last;
        while(pt[idx] > 0) {
            int tmp = (p[idx][pt[idx]-1]-1)%13;
            last = p[idx][pt[idx]-1];
            pt[idx]--;
            idx = tmp;
            cnt++;
        }
        printf("%02d,%c%c\n", cnt, putrank((last-1)%13+1), putsuit((last-1)/13));

    }
    return 0;
}
