#include <stdio.h>

int main() {
    int n, t, a, b, c, abc[501][3] = {}, ok[501] = {};
    for(a = 0; a < 20; a ++) {
        for(b = 0; b < a; b++) {
            for(c = 0; c < b; c++) {
                int N = 0;
                if(a >= 3)  N += a*(a-1)*(a-2)/6;
                if(b >= 2)  N += b*(b-1)/2;
                if(c >= 1)  N += c;
                if(N > 500) break;
                if(ok[N] == 0) {
                    ok[N] = 1;
                    abc[N][0] = a, abc[N][1] = b, abc[N][2] = c;
                }
            }
        }
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        printf("%d%d%d\n", abc[n][0], abc[n][1],  abc[n][2]);
    }
    return 0;
}
