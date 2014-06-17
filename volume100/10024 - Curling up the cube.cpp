#include <stdio.h>
char kind[11][4][6] = {
    {"10000",
     "11110",
     "10000"},
    {"10000",
     "11110",
     "01000"},
    {"10000",
     "11110",
     "00100"},
    {"10000",
     "11110",
     "00010"},
    {"01000",
     "11110",
     "01000"},
    {"01000",
     "11110",
     "00100"},
    {"11000",
     "01110",
     "01000"},
    {"11000",
     "01110",
     "00100"},
    {"11000",
     "01110",
     "00010"},
    {"11100",
     "00111",
     "00000"},
    {"11000",
     "01100",
     "00110"},
};
void rotate(int g[][6]) {
    int i, j, t[6][6];
    for(i = 0; i < 6; i++)
        for(j = 0; j < 6; j++)
            t[i][j] = g[5-j][i];
    for(i = 0; i < 6; i++)
        for(j = 0; j < 6; j++)
            g[i][j] = t[i][j];
}
void upturn(int g[][6]) {
    int i, j, t[6][6];
    for(i = 0; i < 6; i++)
        for(j = 0; j < 6; j++)
            t[i][j] = g[i][5-j];
    for(i = 0; i < 6; i++)
        for(j = 0; j < 6; j++)
            g[i][j] = t[i][j];
}
int check(int g[][6]) {
    int i, j, p, q, k;
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            for(k = 0; k < 11; k++) {
                for(p = 0; p < 3; p++)
                    for(q = 0; q < 5; q++) {
                        if(kind[k][p][q] == '0')
                            continue;
                        if(i+p >= 6 || j+q >= 6 || g[i+p][j+q] != kind[k][p][q])
                            p = 10, q = 10;
                    }
                if(p == 3)
                    return 1;
            }
        }
    }
    return 0;
}
int sol(int g[][6]) {
    int i, j;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 4; j++) {
            if(check(g))
                return 1;
            rotate(g);
        }
        upturn(g);
    }
    return 0;
}
int main() {
    int t, i, j;
    int g[6][6];
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < 6; i++)
            for(j = 0; j < 6; j++)
                scanf("%d", &g[i][j]), g[i][j] += '0';
        if(sol(g))
            puts("correct");
        else
            puts("incorrect");
        if(t)
            puts("");
    }
    return 0;
}
