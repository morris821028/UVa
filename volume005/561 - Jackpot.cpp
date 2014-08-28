#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;


int main() {
    int testcase;
    int A, B, C;
    char sa[1024], sb[1024], sc[1024];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d %d", &A, &B, &C);
        scanf("%s %s %s", sa, sb, sc);
        int cntA[26] = {}, cntB[26] = {}, cntC[26] = {};
        for (int i = 0; sa[i]; i++) {
            cntA[sa[i] - 'A']++;
        }
        for (int i = 0; sb[i]; i++) {
            cntB[sb[i] - 'A']++;
        }
        for (int i = 0; sc[i]; i++) {
            cntC[sc[i] - 'A']++;
        }
        double ret = 0;
        for (int i = 0; i < 26; i++) {
            ret += cntA[i] * cntB[i] * cntC[i] * 7.0 / A/ B/ C * 2;
            ret += cntA[i] * cntB[i] * cntC[i] * 10.0 / A/ B/ C;
            ret += cntA[i] * cntB[i] * cntC[i] * 5.0 / A/ B/ C * 2;
        }
        printf("%.4lf\n", ret);
    }
    return 0;
}
/*
 2
 3 4 6
 AAB
 BABA
 BBAAAB
 12 15 18
 CCCCCCCCCCCC
 CCCCCCCCCCCCCCC
 CCCCCCCCCCCCCCCCCC
*/