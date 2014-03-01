#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        int ans = 0, i, j, k, t;
        char c[3][3], J[3];
        int x[3], y[3];
        for(i = 0; i < 3; i++)
            scanf("%s %d %d", &c[i], &x[i], &y[i]);
        scanf("%s", &J);
        int judge = 0;
        switch(J[0]) {
            case 'R':judge = 1;break;
            case 'Y':judge = 2;break;
            case 'B':judge = 4;break;
            case 'O':judge = 3;break;
            case 'P':judge = 5;break;
            case 'G':judge = 6;break;
            case 'D':judge = 7;break;
        }
        for(t = 0; t <= n; t++) {
            int color[8] = {};
            for(i = 0; i < n; i++) {
                for(j = 0; j < n; j++) {
                    int RYB = 0;
                    for(k = 0; k < 3; k++) {
                        int lx = x[k]-t, rx = x[k]+t;
                        int ly = y[k]-t, ry = y[k]+t;
                        if(lx <= i && i <= rx && ly <= j && j <= ry) {
                            if(c[k][0] == 'R')  RYB |= 1;
                            if(c[k][0] == 'Y')  RYB |= 2;
                            if(c[k][0] == 'B')  RYB |= 4;
                        }
                    }
                    color[RYB]++;
                }
            }
            if(color[judge] > ans)
                ans = color[judge];
        }
        printf("%d\n", ans);
    }
    return 0;
}
