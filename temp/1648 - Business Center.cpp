#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
// binary search
int main() {
    int n, m, u, d;
    while (scanf("%d %d", &n, &m) == 2) {
        int ret = 0x3f3f3f3f;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &u, &d);
            int l = 0, r = n, mid;
            while (l <= r) {
                mid = (l + r)/2;
                int lv = u * mid - (n - mid) * d;
                if (lv > 0)
                    r = mid - 1, ret = min(ret, lv);
                else
                    l = mid + 1;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}