#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int main() {
    int n, x, y, z, d;
    while(scanf("%d", &n) == 1 && n) {
        int lx, ly, lz, rx, ry, rz;
        scanf("%d %d %d %d", &x, &y, &z, &d);
        lx = x, ly = y, lz = z;
        rx = x+d, ry = y+d, rz = z+d;
        n--;
        while(n--) {
            scanf("%d %d %d %d", &x, &y, &z, &d);
            lx = max(lx, x);
            ly = max(ly, y);
            lz = max(lz, z);
            rx = min(rx, x+d);
            ry = min(ry, y+d);
            rz = min(rz, z+d);
        }
        long long ans;
        ans = max(0, (rx-lx)*(ry-ly)*(rz-lz));
        printf("%lld\n", ans);
    }
    return 0;
}
