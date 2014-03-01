#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int t, cases = 0, n, x;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int ret = 0;
        while(n--) {
            scanf("%d", &x);
            ret = max(ret, x);
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
