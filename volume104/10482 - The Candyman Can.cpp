#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int main() {
    int t, n, cases = 0;
    int A[35], i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int sum = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            sum += A[i];
        }
        int mark[13005] = {}; // [645][645]
        int x, y;
        vector<int> X, Y;
        X.push_back(0);
        Y.push_back(0);
        for(i = 0; i < n; i++) {
            int tx_size = X.size();
            for(j = 0; j < tx_size; j++) {
                x = X[j], y = Y[j];
                if(!GET((x+A[i])*645+y)) {
                    SET((x+A[i])*645+y);
                    X.push_back(x+A[i]);
                    Y.push_back(y);
                }
                if(!GET(x*645+y+A[i])) {
                    SET(x*645+y+A[i]);
                    X.push_back(x);
                    Y.push_back(y+A[i]);
                }
            }
        }
        int ans = 0xfffffff, tx_size = X.size();
        int a, b;
        for(i = 1; i < tx_size; i++) {
            a = max(X[i], max(Y[i], sum-X[i]-Y[i]));
            b = min(X[i], min(Y[i], sum-X[i]-Y[i]));
            ans = min(ans, a-b);
        }
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
