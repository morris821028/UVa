#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
int main() {
    int n;
    int res[] =
    {1, 1, 1, 3, 8, 21, 43, 69, 102, 145,
    197, 261, 336, 425, 527, 645, 778, 929, 1097, 1285,
    1492, 1721, 1971, 2245, 2542, 2865, 3213, 3589};
    int cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        /*int a[30], i;
        for(i = 0; i < n; i++)
            a[i] = i;
        set<int> S;
        do {
            int sum = 0;
            for(i = 1; i < n; i++)
                sum += a[i]*a[i-1];
            sum += a[0]*a[n-1];
            S.insert(sum);
        } while(next_permutation(a, a+n));
        printf("%d\n", S.size());*/
        printf("Case #%d: %d\n", ++cases, res[n-1]);
    }
    return 0;
}
/*
1
1
1
3
8
21
43
69
102
145
197
*/
