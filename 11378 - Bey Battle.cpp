#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct Pt {
    int x, y;
    bool operator<(const Pt &a) const {
        if(x != a.x)
            return x < a.x;
        return y < a.y;
    }
};
Pt D[100005];
void closestPair(int l, int r, int &ret) {
    if(l >= r)  return;
    int m = (l+r)/2;
    closestPair(l, m, ret);
    closestPair(m+1, r, ret);
    static int i, j;
    for(i = m; i >= l; i--) {
        if(D[m].x-D[i].x >= ret)
            break;
        for(j = m+1; j <= r; j++) {
            if(D[j].x-D[i].x >= ret)
                break;
            ret = min(ret, max(D[j].x-D[i].x, abs(D[j].y-D[i].y)));
        }
    }
}
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d %d", &D[i].x, &D[i].y);
        sort(D, D+n);
        int ret = 0xfffffff;
        closestPair(0, n-1, ret);
        printf("%d\n", ret);
    }
    return 0;
}
