#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int L = 1, R = 1, Li, Ri;
        int dpl = 0, dpr = 0, tdpl, tdpr;
        int i;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &Li, &Ri);
            tdpl = min(dpl+abs(L-Li), dpr+abs(R-Li))+1;
            tdpr = min(dpr+abs(R-Ri), dpl+abs(L-Ri))+1;
            dpr = tdpl + Ri-Li;
            dpl = tdpr + Ri-Li;
            L = Li, R = Ri;
        }
        printf("%d\n", min(dpl+n-Li, dpr+n-Ri)-1);
    }
    return 0;
}
