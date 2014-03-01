#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
    int n, m, cases = 0;
    int B[10005], S[10005];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        int mn = 0xfffffff, i;
        for(i = 0; i < n; i++)
            scanf("%d", B+i), mn = min(mn, B[i]);
        for(i = 0; i < m; i++)
            scanf("%d", S+i);
        if(n <= m)
            printf("Case %d: 0\n", ++cases);
        else
            printf("Case %d: %d %d\n", ++cases, n-m, mn);
    }
    return 0;
}
