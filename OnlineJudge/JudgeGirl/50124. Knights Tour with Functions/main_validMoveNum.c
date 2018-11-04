#include <stdio.h>
#include "validMoveNum.h"
#define MAXN 100
int r[MAXN*MAXN];
int c[MAXN*MAXN];
int visited[MAXN][MAXN]={0};
int move[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
void print_p(int p[]){
    for(int j=0; j<8; j++){
        printf("%d",p[j]);
        if(j==7)
            printf("\n");
        else
            printf(" ");
    }
    return;
}
int main(){
    int n,m;
    scanf("%d%d", &n, &m);
    for(int i=0; i<m; i++){
        scanf("%d%d", &r[i], &c[i]);
        visited[r[i]][c[i]] = 1;
    }
    int p[8];
    for(int i=0; i<m; i++){ //each knight
        for(int j=0; j<8; j++)
            p[j] = validMoveNum(r[i]+move[j][0], c[i]+move[j][1], n, visited);   
        print_p(p);   
    }
    return 0;
}
