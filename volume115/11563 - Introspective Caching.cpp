#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <algorithm>
using namespace std;

static const int MAXN = 131072;
static int A[MAXN], P[MAXN];
int main() {
    int n, m, q;
    while (scanf("%d %d %d", &n, &m, &q) == 3) {
        for (int i = 0; i < q; i++)
            scanf("%d", &A[i]);
        static int B[MAXN];
        memset(B, 0x3f, sizeof(B[0])*m);
        for (int i = q-1; i >= 0; i--) {
            int u = A[i];
            P[i] = B[u], B[u] = i;
        }
        
        set<pair<int, int>> S;
        memset(B, -1, sizeof(B[0])*m);
        int miss = 0;
        for (int i = 0; i < q; i++) {
            int u = A[i];
            if (S.size() >= n) {
                if (B[u] != -1) {
                    S.erase({B[u], u});
                } else {
                    miss++;
                    auto t = *S.rbegin();
                    S.erase(t);
                    B[t.second] = -1;
                }
            } else {
                if (B[u] != -1) {
                    S.erase({B[u], u});
                } else {
                    miss++;
                }
            }
            
            S.insert({P[i], u});
            B[u] = P[i];
        }
        printf("%d\n", miss);
    }
    return 0;
}
/*
 1 2 3
 0
 0
 1
 3 4 8
 0
 1
 2
 3
 3
 2
 1
 0
 
 3 7 7
 5
 1
 1
 3
 0
 2
 6
 2 2 10
 1
 1
 1
 0
 0
 0
 1
 1
 0
 0
*/

