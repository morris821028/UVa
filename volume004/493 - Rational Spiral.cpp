#include <stdio.h>
#include <stdlib.h>
#include <set>
using namespace std;
set<unsigned long long> S;
int gcd(int x, int y) {
    int t;
    while(x%y)
        t = x, x = y, y = t%y;
    return y;
}
int x = 0, y = 1, i, j;
int X[500005], Y[500005];
int idx = 0;
void check() {
    if(!x)  return;
    static int g, tx, ty;
    static unsigned long long s;
    tx = x, ty = y;
    g = gcd(abs(y), abs(x));
    tx /= g, ty /= g;
    if(tx < 0)  ty = -ty, tx = -tx;
    X[idx] = tx, Y[idx] = ty;
    s = ((unsigned long long)tx)<<32 | (unsigned)ty;
    if(S.find(s) == S.end())
        idx++, S.insert(s);
}
int main() {
    for(i = 2; idx <= 500000; i += 2) {
        for(j = 0; j < i && idx <= 500000; j++, x++)
            check();
        x--, y--;
        for(j = 0; j < i && idx <= 500000; j++, y--)
            check();
        y++, x--;
        for(j = 0; j < i && idx <= 500000; j++, x--)
            check();
        x++, y++;
        for(j = 0; j < i && idx <= 500000; j++, y++)
            check();
    }
    int n;
    while(scanf("%d", &n) == 1) {
        printf("%d / %d\n", Y[n], X[n]);
    }
    return 0;
}
