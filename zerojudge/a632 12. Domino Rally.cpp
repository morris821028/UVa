#include <stdio.h>

int dice[30][2] = {
{0,0},{0,0},{0,1},{0,2},{0,3},
{0,4},{0,5},{0,6},{1,1},{1,2},
{1,3},{1,4},{1,5},{1,6},{2,2},
{2,3},{2,4},{2,5},{2,6},{3,3},
{3,4},{3,5},{3,6},{4,4},{4,5},
{4,6},{5,5},{5,6},{6,6},{0,0}};
int main() {
    int D[150], n, i, j, p, q;
    char E[150];
    do {
        n = 0;
        while(1) {
            if(scanf("%d %c", &D[n], &E[n]) != 2)
                return 0;
            if(D[n] == 0)   break;
            n++;
        }
        int update;
        do {
            update = 0;
            for(i = 1; i < n; i++) {
                if(E[i-1] == 'B')   p = dice[D[i-1]][0];
                else   p = dice[D[i-1]][1];
                if(E[i] == 'B')     q = dice[D[i]][1];
                else   q = dice[D[i]][0];
                if(p == q) {
                    update = 1;
                    for(j = i-1, i++; i < n; i++, j++)
                        D[j] = D[i], E[j] = E[i];
                    n -= 2;
                    break;
                }
            }
        } while(update);
        for(i = 0; i < n; i++)
            printf("%d ", D[i]);
        if(n == 0)  printf("DATASET CLEARED");
        puts("");
    } while(1);
    return 0;
}
