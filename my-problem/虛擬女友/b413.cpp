#include <bits/stdc++.h>
using namespace std;

const int MAXN = 65536;
vector<int> son[MAXN];
int parent[MAXN], A[MAXN];
int main() {
    int testcase, n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        long long tot_pair = 0;
        int x, y;
        map< pair<int, int>, int > R;
        
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            son[i].resize(1, i);
            R[pair<int, int>(i, A[i])] = 1;
        }
        
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            x--, y--;
            x = parent[x], y = parent[y];
            if (x != y) { // merge small to large
                if (son[x].size() > son[y].size())
                    swap(x, y);
                for (auto &e: son[x]) {
                    pair<int, int> t(parent[e], A[e]);
                    R[t]--;
                    if (R[t] == 0)  R.erase(t);
                    parent[e] = y;
                    son[y].push_back(e);
                    tot_pair += R[pair<int, int>(parent[e], A[e])];
                }
                for (auto &e: son[x])
                    R[pair<int, int>(parent[e], A[e])]++;
                son[x].clear();
            }
            printf("%lld\n", tot_pair);
        }
    }
    return 0;
}