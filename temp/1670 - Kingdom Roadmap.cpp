#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
#include <vector>
using namespace std;
#define MAXN 262144
// building way, ad-Hoc
vector<int> g[MAXN];
vector< pair<int, int> > ret;
vector<int> dfs(int u, int p) {
    vector<int> leaf1, leaf2, A;
    if (g[u].size() == 1) {
        leaf1.push_back(u);
        return leaf1;
    }
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p)
            continue;
        vector<int> t = dfs(v, u);
        if (t.size()%2 == 0)
            leaf2.insert(leaf2.end(), t.begin(), t.end());
        if (t.size()%2 == 1)
            leaf1.insert(leaf1.end(), t.begin(), t.end());
    }
    // make to connect leaf in cross
    A = leaf1;
    A.insert(A.end(), leaf2.begin(), leaf2.end());
    if (A.size()%2 == 1) {
        leaf1.clear();
        leaf1.push_back(A[A.size()-1]);
        for (int i = 0; i+1 < A.size(); i += 2) // must connect from different subtree.
            ret.push_back(make_pair(A[i], A[i+1]));
        return leaf1;
    } else {
        leaf2.clear();
        leaf2.push_back(A[0]);
        leaf2.push_back(A[A.size()-1]);
        for (int i = 1; i+1 < A.size(); i += 2)
            ret.push_back(make_pair(A[i], A[i+1]));
        return leaf2;
    }
}
int main() {
    int N, x, y;
    while (scanf("%d", &N) == 1) {
        for (int i = 0; i <= N; i++)
            g[i].clear();
        for (int i = 1; i < N; i++) {
            scanf("%d %d", &x, &y);
            g[x].push_back(y);
            g[y].push_back(x);
        }
        
        ret.clear();
        for (int i = 1; i <= N; i++) {
            if (g[i].size() > 1 || N == 2) {
                vector<int> t = dfs(i, -1);
                if (t.size() == 1) {
                    ret.push_back(make_pair(t[0], i));
                } else if (t.size() == 2) {
                    ret.push_back(make_pair(t[0], t[1]));
                }
                break;
            }
        }
        
        printf("%d\n", (int) ret.size());
        for (int i = 0; i < ret.size(); i++) {
            printf("%d %d\n", ret[i].first, ret[i].second);
        }
    }
    return 0;
}
/*
 5
 1 2
 2 3
 3 4
 3 5
 4
 1 2
 1 3
 1 4
 */
