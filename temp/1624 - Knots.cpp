#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#define MAXN 1048576
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;

struct Node {
    int l, r;
    int face;
} nodes[MAXN];
int F[MAXN], used[MAXN];
void removeNode(int idx) {
    used[idx] = 1;
    nodes[nodes[idx].r].l = nodes[idx].l;
    nodes[nodes[idx].l].r = nodes[idx].r;
}
int main() {
    int testcase, cases = 0, L, P, x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &L, &P);
        for (int i = 0; i < L; i++) {
            nodes[i].l = i-1, nodes[i].r = i+1, F[i] = 0, used[i] = 0;
        }
        nodes[0].l = L-1, nodes[L-1].r = 0;
        for (int i = 0; i < P; i++) {
            scanf("%d %d", &x, &y);
            nodes[x].face = y;
            nodes[y].face = x;
            F[x] = 1, F[y] = -1;
        }
        
        int st = 0, listSize = 2 * P;
        
        for (int i = 0; i < L; i++) {
            if (!F[i])
                removeNode(i);
        }
        
        while (listSize) {
            int update = 0;
            while (used[st])    st++;
            for (int i = nodes[st].r; !update && i != st; i = nodes[i].r) {
                x = i, y = nodes[i].r;
                if (F[x] == F[y] && (nodes[nodes[y].face].r == nodes[x].face ||
                                     nodes[nodes[x].face].r == nodes[y].face)) {
                    removeNode(x), removeNode(nodes[x].face);
                    removeNode(y), removeNode(nodes[y].face);
                    listSize -= 4;
                    update = 1;
                } // Passing
                else if (y == nodes[x].face) {
                    removeNode(x), removeNode(y);
                    listSize -= 2;
                    update = 1;
                } // Self loop
            }
            if (!update)    break;
        }
        printf("Case #%d: %s\n", ++cases, listSize ? "NO" : "YES");
    }
    return 0;
}
/*
 3
 20 5
 0 8
 2 10
 4 12
 15 5
 18 7
 50 7
 10 42
 28 15
 27 39
 18 31
 38 32
 21 37
 24 34
 20 5
 0 8
 10 2
 4 12
 15 5
 7 18
*/