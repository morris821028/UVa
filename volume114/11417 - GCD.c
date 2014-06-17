#include <stdio.h>
int gcd(int x, int y) {
    int tmp;
    while(x%y) {
        tmp = x, x = y, y = tmp%y;
    }
    return y;
}
int main() {
    int n, i, j;
    int ans[501] = {}, map[501][501] = {};
    for(i = 1; i < 501; i++) {
        for(j = i+1; j < 501; j++) {
            map[i][j] = map[i][j-1] + gcd(i, j);
            ans[j] += map[i][j];
        }
    }
    while(scanf("%d", &n) == 1 && n) {
        printf("%d\n", ans[n]);
    }
    return 0;
}
