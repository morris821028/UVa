#include <stdio.h>

int main() {
    int i, j, idx = 2;
    int px[100025], py[100025];
    px[1] = py[1] = 0;
    for(i = 1; idx < 100005; i++) {
        px[idx] = px[idx-1], py[idx] = py[idx-1]+1;
        idx++;
        for(j = 1; j < i && idx < 100005; j++, idx++)
            px[idx] = px[idx-1]-1, py[idx] = py[idx-1]+1;

        px[idx] = px[idx-1]-1, py[idx] = py[idx-1];
        idx++;
        for(j = 1; j < i && idx < 100005; j++, idx++)
            px[idx] = px[idx-1]-1, py[idx] = py[idx-1];

        px[idx] = px[idx-1], py[idx] = py[idx-1]-1;
        idx++;
        for(j = 1; j < i && idx < 100005; j++, idx++)
            px[idx] = px[idx-1], py[idx] = py[idx-1]-1;

        px[idx] = px[idx-1]+1, py[idx] = py[idx-1]-1;
        idx++;
        for(j = 1; j < i && idx < 100005; j++, idx++)
            px[idx] = px[idx-1]+1, py[idx] = py[idx-1]-1;

        px[idx] = px[idx-1]+1, py[idx] = py[idx-1];
        idx++;
        for(j = 1; j < i && idx < 100005; j++, idx++)
            px[idx] = px[idx-1]+1, py[idx] = py[idx-1];

        px[idx] = px[idx-1], py[idx] = py[idx-1]+1;
        idx++;
        for(j = 1; j < i && idx < 100005; j++, idx++)
            px[idx] = px[idx-1], py[idx] = py[idx-1]+1;
    }
    while(scanf("%d", &idx) == 1)
        printf("%d %d\n", px[idx], py[idx]);
    return 0;
}
