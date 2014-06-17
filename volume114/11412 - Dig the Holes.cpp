#include <stdio.h>

int main() {
    int testcase;
    int mapped[128] = {};
    mapped['R'] = 0, mapped['G'] = 1;
    mapped['B'] = 2, mapped['Y'] = 3;
    mapped['O'] = 4, mapped['V'] = 5;
    scanf("%d", &testcase);
    while(testcase--) {
        int na, nb, ma, mb;
        char M[50], N[50];
        int i, j, k;
        // R, G, B, Y, O, V
        scanf("%s %d %d", N, &na, &nb);
        for(i = 0; i < 4; i++)
            N[i] = mapped[N[i]];
        scanf("%s %d %d", M, &ma, &mb);
        for(i = 0; i < 4; i++)
            M[i] = mapped[M[i]];
        int i1, i2, i3, i4;
        int found = 0;
        for(i1 = 0; i1 < 6; i1++)
        for(i2 = 0; i2 < 6; i2++)
        for(i3 = 0; i3 < 6; i3++)
        for(i4 = 0; i4 < 6; i4++) {
            int O[4] = {i1, i2, i3, i4};
            if(i1 == i2 || i1 == i3 || i1 == i4 ||
                i2 == i3 || i2 == i4 || i3 == i4)
                    continue;
            int a = 0, b = 0;
            for(i = 0; i < 4; i++) {
                if(N[i] == O[i]) {
                    a++;
                    O[i] = -1;
                }
            }
            for(i = 0; i < 4; i++) {
                if(N[i] == O[i])    continue;
                for(j = 0; j < 4; j++) {
                    if(N[i] == O[j] && N[j] != O[j]) {
                        O[j] = -1;
                        b++;
                    }
                }
            }
            if(a != na || b != nb)
                continue;
            O[0] = i1, O[1] = i2, O[2] = i3, O[3] = i4;
            a = 0, b = 0;
            for(i = 0; i < 4; i++) {
                if(M[i] == O[i]) {
                    a++;
                    O[i] = -1;
                }
            }
            for(i = 0; i < 4; i++) {
                if(M[i] == O[i])    continue;
                for(j = 0; j < 4; j++) {
                    if(M[i] == O[j] && M[j] != O[j]) {
                        O[j] = -1;
                        b++;
                    }
                }
            }
            if(a != ma || b != mb)
                continue;
            found = 1;
            i1 = i2 = i3 = i4 = 6;
        }
        puts(found ? "Possible" : "Cheat");
    }
    return 0;
}
