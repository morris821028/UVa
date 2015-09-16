#include <stdio.h>
#include <algorithm>
using namespace std;
int g[512][512];
int main() {
    int n, m, cases = 0;
    while (scanf("%d %d", &n, &m) == 2) {
        int row[512] = {}, col[512] = {};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &g[i][j]);
                row[i] += g[i][j];
                col[j] += g[i][j];
            }
        }
        
        int mxr = 0, mxc = 0;
        for (int i = 0; i < n; i++)
            if (row[i] > row[mxr])   mxr = i;
        for (int i = 0; i < m; i++)
            if (col[i] > col[mxc])   mxc = i;
        int test = row[mxr] + col[mxc] - g[mxr][mxc];
        int acc = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                acc = max(acc, row[i] + col[j] - g[i][j]);
            }
        }
        printf("Case %d: %s\n", ++cases, acc == test ? "Weak" : "Strong");
    }
    return 0;
}