#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
#include <iostream>
#include <sstream>
using namespace std;
#define MAXN 64
int g[MAXN][MAXN];
/*
 During every iteration each leaf is contracted with its parent, until
 
 * 1 leaf left
 * 2 leaves left, and they connected by a single edge
 
 A vertex i is a leaf only when d[j][i]+d[i][k]>d[j][k] for all vertices j, k.
 If a leaf i is still a leaf(instead of becoming an internal node) after contraction, then there is a router with degree n+2, where n is the number of vertices having zero distance with i.
 Special case: Router's degree is n+1 if it is the final iteration, ending with condition 1 above
 */
int isLeaf(int N, int x, int used[]) {
    int ret = 1;
    for (int j = 0; j < N && ret; j++) {
        for (int k = 0; k < N && ret; k++) {
            if (used[j] || used[k]) // 0: leaf, 1: inner, 2: delete
                continue;
            if (j == k || x == j || x == k)
                continue;
            ret &= g[j][x] + g[x][k] > g[j][k];
        }
    }
    return ret;
}
int main() {
    int N;
    while (scanf("%d", &N) == 1 && N) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                scanf("%d", &g[i][j]);
        int used[MAXN] = {};
        vector<int> ret;
        while (true) {
            vector<int> leaf;
            for (int i = 0; i < N; i++) {
                if (used[i] == 2) // delete
                    continue;
                int b = isLeaf(N, i, used);
                if (b)
                    leaf.push_back(i);
                else
                    used[i] = 1;
            }
            int x = leaf[0];
            for (int i = 0; i < N; i++) {
                if (i == x)
                    continue;
                if (g[x][i])
                    g[x][i]--, g[i][x]--;
            }
//            printf("contract %d\n", x);
//            for (int i = 0; i < N; i++) {
//                printf("%d%c", used[i], i == N-1 ? '\n' : ' ');
//            }
//            puts("");
//            for (int i = 0; i < N; i++, puts("")) {
//                for (int j = 0; j < N; j++) {
//                    printf("%d ", g[i][j]);
//                }
//            }
            if (isLeaf(N, x, used)) {
                int router = 0;
                for (int i = 0; i < N; i++) {
                    if (used[i] == 2 || i == x)
                        continue;
                    if (g[x][i] == 0) {
                        router++;
                        used[i] = 2;
                    }
                }
                ret.push_back(router + 2);
            }
            if (leaf.size() == 1 || (leaf.size() == 2 && g[leaf[0]][leaf[1]] == 1))
                break;
        }
        sort(ret.begin(), ret.end());
        for (int i = 0; i < ret.size(); i++) {
            printf("%d%c", ret[i], i == ret.size()-1 ? '\n' : ' ');
        }
    }
    return 0;
}
/*
 4
 0  2  2  2
 2  0  2  2
 2  2  0  2
 2  2  2  0
 4
 0  2  4  4
 2  0  4  4
 4  4  0  2
 4  4  2  0
 2
 0 12
 12  0
 3
 0 3 3
 3 0 2
 3 2 0
 0
 */
