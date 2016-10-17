#include "game_of_cell.h"
#include <stdlib.h>
#include <string.h>

void game_of_cell(int in[][50], int out[][50], int n) {
    const int m = 50;
    char g[2][52][52] = {};
    char stab[3][9] = {
        {0, 0, 0, 2, 0, 0, 0, 0, 0},
        {1, 1, 2, 1, 1, 1, 1, 1, 1},
        {0, 0, 2, 2, 1, 1, 1, 1, 1}
    };
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            g[0][i][j] = in[i-1][j-1];
        }
    }
#define UNLOOP { \
    h = (g[0][i-1][j-1]>>1) + (g[0][i-1][j]>>1) + (g[0][i-1][j+1]>>1) \
        + (g[0][i][j-1]>>1) + (g[0][i][j+1]>>1) \
        + (g[0][i+1][j-1]>>1) + (g[0][i+1][j]>>1) + (g[0][i+1][j+1]>>1); \
    g[1][i][j] = stab[g[0][i][j]][h]; j++; \
}
#define UNLOOP4 {UNLOOP UNLOOP UNLOOP UNLOOP}
#define UNLOOP8 {UNLOOP4 UNLOOP4}
    for (int it = n-1; it >= 0; it--) {
        for (int i = 1; i <= m; i++) {
            int j = 1, h;
            for (; j + 8 <= m; )
                UNLOOP8;
            for (; j <= m; )
                UNLOOP;
        }
        memcpy(g[0], g[1], sizeof(g[0]));
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++)
            out[i-1][j-1] = g[0][i][j];
    }
}

