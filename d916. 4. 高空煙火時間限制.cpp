#include<stdio.h>
#include<stdlib.h>
#define Mod 10000
short P[3011][3011] = {0};
int PASCAL() {
	int a, b;
    P[0][0] = 1;
    for(a = 1; a <= 3010; a++) {
        P[a][0] = 1;
        for(b = 1; b < a; b++)
            P[a][b] = (P[a-1][b] + P[a-1][b-1])%Mod;
        P[a][a] = 1;
    }
}
main() {
    int N, M;
    PASCAL();
	while(scanf("%d %d", &N, &M) == 2) {
        int Ans=0, a;
        for(a = 0;a <= N + 1; a++) {
            if(N - (a-1)*M >= 0) {
                Ans = (Ans + P[N - (a-1)*M][a])%Mod;
            }
            else break;
        }
        printf("%d\n",Ans);
    }
	return 0;
}
