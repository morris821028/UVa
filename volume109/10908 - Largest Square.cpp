#include <stdio.h>
#include <stdlib.h>

int main() {
    int T;
    char map[102][102];
    int i, M, N, Q, x, y;
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d %d", &M, &N, &Q);
        getchar();
        for(i = 0; i < M; i++)
            gets(map[i]);
        printf("%d %d %d\n", M, N, Q);

        while(Q--) {
            scanf("%d %d", &x, &y);
            int ans = 1;
            int i, a, b;
            for(i = 0; i <= M || i <= N; i++) {
                int flag = 0;
                for(a = x-i; a <= x+i; a++) {
                    for(b = y-i; b <= y+i; b++) {
                        if(a < 0 || b < 0 || a >= M || b >= N) {
                            flag = 1;break;
                        }
                        if(map[a][b] != map[x][y])
                            flag = 1;
                    }
                }
                if(flag == 0) {
                    if(ans < 2*i+1)
                        ans = i*2+1;
                } else
					break; 
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
