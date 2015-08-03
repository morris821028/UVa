#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 65536;
int parent[MAXN], weight[MAXN];
int findp(int x) {
    return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y)	return 0;
    if (weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}

int main() {
    int testcase, n, m;
    int A[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        long long tot_pair = 0;
        int x, y;
        
        for (int i = 0; i < n; i++) {
            parent[i] = i, weight[i] = 1;
        }
        
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            x--, y--;
            x = findp(x), y = findp(y);
            if (x != y) {
                vector<int> b;
                map<int, int> a;
                for (int j = 0; j < n; j++) {
                    if (findp(j) == x)
                        a[A[j]]++;
                    if (findp(j) == y)
                        b.push_back(A[j]);
                }
                for (int j = 0; j < b.size(); j++)
                    tot_pair += a[b[j]];
                joint(x, y);
            }
            printf("%lld\n", tot_pair);
        }
    }
    return 0;
}