#include <stdio.h>

int main() {
    int n, idx = 2, i, j;
    int x[32767], y[32767];
    x[1] = 0, y[1] = 0;
    for(i = 1; idx < 32767; i++) {
        if(i&1) {
            x[idx] = x[idx-1];
            y[idx] = y[idx-1]+1;
            idx++;
            for(j = 0; j < i && idx < 32767; j++)
                x[idx] = x[idx-1]+1, y[idx] = y[idx-1], idx++;
            for(j = 0; j < i && idx < 32767; j++)
                x[idx] = x[idx-1], y[idx] = y[idx-1]-1, idx++;
        } else {
            x[idx] = x[idx-1]+1;
            y[idx] = y[idx-1];
            idx++;
            for(j = 0; j < i && idx < 32767; j++)
                x[idx] = x[idx-1], y[idx] = y[idx-1]+1, idx++;
            for(j = 0; j < i && idx < 32767; j++)
                x[idx] = x[idx-1]-1, y[idx] = y[idx-1], idx++;
        }
    }
    while(scanf("%d", &n) == 1 && n) {
        printf("%d %d\n", x[n], y[n]);
    }
    return 0;
}
