#include <stdio.h>
int B[2][5][5];
void ban(int b[][5], int x) {
    int i, j;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(b[i][j] == x) {
                b[i][j] = 0;
                return;
            }
        }
    }
}
int bingo(int b[][5]) {
    int i, j;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(b[i][j])
                break;
        }
        if(j == 5)  return 1;
        for(j = 0; j < 5; j++) {
            if(b[j][i])
                break;
        }
        if(j == 5)  return 1;
    }
    for(i = 0; i < 5; i++)
        if(b[i][i])
            break;
    if(i == 5)  return 1;
    for(i = 0; i < 5; i++)
        if(b[4-i][i])
            break;
    if(i == 5)  return 1;
    return 0;
}
int main() {
    int t, i, j, x;
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < 5; i++) {
            for(j = 0; j < 5; j++) {
                scanf("%d", &B[0][i][j]);
            }
        }
        for(i = 0; i < 5; i++) {
            for(j = 0; j < 5; j++) {
                scanf("%d", &B[1][i][j]);
            }
        }
        int flag = -1;
        for(i = 0; i < 25; i++) {
            scanf("%d", &x);
            if(flag == -1) {
                ban(B[0], x);
                ban(B[1], x);
                int a = bingo(B[0]), b = bingo(B[1]);
                if(a && b)  flag = 0;
                if(a && !b) flag = 1;
                if(!a && b) flag = 2;
            }
        }
        printf("%d\n", flag);
    }
    return 0;
}
