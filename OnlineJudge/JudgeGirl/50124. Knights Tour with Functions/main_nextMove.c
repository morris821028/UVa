#include <stdio.h>
#include "nextMove.h"
#define MAXN 100
int visited[MAXN][MAXN]={0};
int move[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
int main(){
    int n, m, r, c;
    scanf("%d",&n);
    scanf("%d%d",&r,&c);
    scanf("%d",&m);
    for(int i=0; i<m; i++){
        int a,b;
        scanf("%d%d",&a,&b);
        visited[a][b] = 1;
    }
    printf("%d", nextMove(r, c, n, visited));
}
