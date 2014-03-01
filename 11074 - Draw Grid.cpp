#include <stdio.h>

int main() {
    int S, T, N;
    int cases = 0, i, j;
    char f1[4096], f2[4096];
    while(scanf("%d %d %d", &S, &T, &N) == 3) {
        if(!S && !T && !N)
            break;
        printf("Case %d:\n", ++cases);
        int len = N*S + (N+1)*T;
        f1[len] = f2[len] = '\0';
        for(i = 0; i < len; i++)
            f1[i] = f2[i] = '*';
        for(i = T; i < len; i += S+T) {
            for(j = 0; j < S; j++)
                f2[i+j] = '.';
        }
        for(i = 0; i < N; i++) {
            for(j = 0; j < T; j++)
                puts(f1);
            for(j = 0; j < S; j++)
                puts(f2);
        }
        for(i = 0; i < T; i++)
            puts(f1);
        puts("");
    }
    return 0;
}
