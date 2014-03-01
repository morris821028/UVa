#include<stdio.h>
main() {
    int N, M;
    while(scanf("%d", &N) == 1) {
        int MapN[20][20]={0}, MapM[20][20]={0};
        int a, b, c, x, y;
        for(a = 0; a < N; a++) {
            scanf("%d %d %d", &x, &y, &c);
            MapN[x][y] = c+1;
        }
        scanf("%d", &M);
        for(a = 0; a < M; a++) {
            scanf("%d %d %d", &x, &y, &c);
            MapM[x][y] = c+1;
        }
        int Ans = 0;
        for(a = 0; a < 20; a++)
        	for(b = 0; b < 20; b++)
                if((MapN[a][b] == 1 && MapM[a][b] == 2) || (MapN[a][b] == 2 && MapM[a][b] ==1 ))  Ans += 2;
                else if((MapN[a][b] == 1 && MapM[a][b] == 0) || (MapN[a][b] == 2 && MapM[a][b] == 0) ||
                        (MapN[a][b] == 0 && MapM[a][b] == 1) || (MapN[a][b] == 0 && MapM[a][b] == 2)) 
						Ans += 1;
        printf("%d\n",Ans);
    }
	return 0;
}
