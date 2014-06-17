#include <stdio.h>
#include <algorithm>
#define oo 0xffffff
using namespace std;
int main() {
    int N, K, A[105], i, j, k;
    int g[105][105];
    char s[1000];
    while(scanf("%d %d", &N, &K) == 2) {
        for(i = 0; i < 100; i++)
            for(j = 0; j < 100; j++)
                g[i][j] = oo;
        for(i = 0; i < N; i++)
            scanf("%d", &A[i]);
        while(getchar() != '\n');
        for(i = 0; i < N; i++) {
            gets(s);
            int ed, buf[100], idx = 0;
            for(j = 0; s[j];) {
                while(s[j] == ' ')  j++;
                sscanf(s+j, "%d", &ed);
                while(s[j] != ' ' && s[j])  j++;
                buf[idx++] = ed;
            }
            for(j = 0; j < idx; j++)
                for(k = j+1; k < idx; k++)
                    g[buf[j]][buf[k]] = min(abs(buf[j]-buf[k])*A[i], g[buf[j]][buf[k]]),
                    g[buf[k]][buf[j]] = g[buf[j]][buf[k]];
        }
        int used[100] = {}, DIS[100];
        for(i = 0; i < 100; i++)
            used[i] = 0, DIS[i] = oo;
        DIS[0] = 0;
        for(i = 0; i < 100; i++) {
            int mn = oo, tn;
            for(j = 0; j < 100; j++)
                if(used[j] == 0 && DIS[j] < mn)
                    mn = DIS[j], tn = j;
            if(mn == oo || tn == K) break;
            used[tn] = 1;
            for(j = 0; j < 100; j++)
                if(g[tn][j] && DIS[j] > DIS[tn]+g[tn][j]+60)
                    DIS[j] = DIS[tn]+g[tn][j]+60;
        }
        if(DIS[K] == oo)
            puts("IMPOSSIBLE");
        else if(DIS[K] == 0)
            puts("0");
        else
            printf("%d\n", DIS[K]-60);
    }
    return 0;
}
/*
2 30
10 5
0 1 3 5 7 9 11 13 15 20 99
4 13 15 19 20 25 30
*/
