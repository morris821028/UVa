#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <functional>
#include <deque>
#include <assert.h>
#include <algorithm>
using namespace std;
#define MAXN 305
int g[MAXN][MAXN], n, m;
int main() {
    for (int i = 1; i < MAXN; i++) {
        for (int j = 1; j < MAXN; j++) {
            g[i][j] = __gcd(i, j);
        }
    }
    while (scanf("%d %d", &n, &m) == 2 && n) {
        long long ret = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (g[i][j] == 1) {
                    // a = i, b = j, consider diagonal from left-top to right-buttom
                    // box a * b, left-top (x, y), x < n - a, y < m - b
                    long long way = (n - i) * (m - j);
                    // left-top box and this box, combine to one diagonal (remove duplicate)
                    way -= max(0, n - 2 * i) * max(0, m - 2 * j);
                    ret += way;
                }
            }
        }
        printf("%lld\n", ret * 2);
    }
    return 0;
}
/*

*/