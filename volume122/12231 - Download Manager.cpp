#include <stdio.h>
#include <stack>
#include <algorithm>
#include <string.h>
using namespace std;

int main() {
    int T, n, B;
    int cases = 0;
    while(scanf("%d %d %d", &T, &n, &B) == 3 && T+n+B) {
        double ret = 0, S, P;
        for (int i = 0; i < T; i++) {
            scanf("%lf %lf", &S, &P);
            ret += S * (100 - P) / 100.0;
        }
        printf("Case %d: %.2lf\n\n", ++cases, ret/B);
    }
    return 0;
}

/*
 6 3 90
 100.00 90
 40.40 70
 60.30 70
 40.40 80
 40.40 85
 40.40 88
 1 1 56
 12.34 100
 0 0 0
 */
