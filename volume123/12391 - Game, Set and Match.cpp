#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

double P;
double gameP, tieP, setP, matchP;
double getGame(int sa, int sb, int line) {
    if (sa == line && sa - sb >= 2)
        return 1;
    if (sb == line && sb - sa >= 2)
        return 0;
    if (sa == sb && sa == line - 1) // win two consecutive points X
        return P * P / (1 - 2 * P * (1 - P)); // X = P*P + P*(1 - P)*X + (1 - P)*P*X
    return getGame(sa + 1, sb, line) * P +
        getGame(sa, sb + 1, line) * (1 - P);
}
double getSet(int sa, int sb, int line) {
    if (sa >= line && sa - sb >= 2)
        return 1;
    if (sb >= line && sb - sa >= 2)
        return 0;
    if (sa == sb && sa == line)
        return tieP;
    return getSet(sa + 1, sb, line) * gameP +
    getSet(sa, sb + 1, line) * (1 - gameP);
 
}
int main() {
    while (scanf("%lf", &P) == 1 && P >= 0) {
        gameP = getGame(0, 0, 4);
        tieP = getGame(0, 0, 7);
        setP = getSet(0, 0, 6);
        matchP = setP * setP + setP * setP * (1 - setP) * 2;
        printf("%.11lf %.11lf %.11lf\n", gameP, setP, matchP);
    }
    return 0;
}

/*
 0.5
 0.3
 0.7
 -1 */
