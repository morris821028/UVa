#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <algorithm>
using namespace std;

struct Node {
    int l, r;
};
Node node[131072];
void linkNode(int l, int r) {
    node[r].l = l, node[l].r = r;
}
int main() {
    int n, m, cases = 0;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++)
            node[i].l = i - 1, node[i].r = i + 1;
        node[0].r = 1, node[0].l = n, node[n].r = 0;
        int cmd, X, Y;
        int rflag = 0;
        while (m--) {
            scanf("%d", &cmd);
            if (cmd == 4) {
                rflag = !rflag;
                continue;
            }
            scanf("%d %d", &X, &Y);
            if(cmd == 3) { // swap box X, Y
                if (node[Y].r == X)
                    swap(X, Y);
                if (Y == node[X].r) { // adjacency
                    linkNode(node[X].l, Y), linkNode(X, node[Y].r);
                    linkNode(Y, X);
                } else {
                    int Yl = node[Y].l, Yr = node[Y].r;
                    linkNode(node[X].l, Y), linkNode(Y, node[X].r);
                    linkNode(Yl, X), linkNode(X, Yr);
                }
            } else {
                if (rflag)
                    cmd = 3 - cmd;
                if ((cmd == 1 && node[Y].l == X) || (cmd == 2 && node[Y].r == X))
                    continue;
                if (cmd == 1) { //move box X to the left to Y
                    linkNode(node[X].l, node[X].r);
                    linkNode(node[Y].l, X), linkNode(X, Y);
                } else { //move box X to the right to Y
                    linkNode(node[X].l, node[X].r);
                    linkNode(X, node[Y].r), linkNode(Y, X);
                }
            }
//            for (int i = 1, p = 0; i <= n; i++) {
//                p = node[p].r;
//                printf("[%d] - ", p);
//            }
//            puts("");
        }
        long long ret = 0;
        for (int i = 1, p = 0; i <= n; i++) {
            p = node[p].r;
//            printf("[%d] - ", p);
            if (i&1)
                ret += p;
        }
//        puts("");
        if (rflag && n%2 == 0) {
            ret = (long long)(n) * (n + 1)/2 - ret;
        }
        printf("Case %d: %lld\n", ++cases, ret);
    }
    return 0;
}
/*
 6 4
 1 1 4
 2 3 5
 3 1 6
 4
 6 3
 1 1 4
 2 3 5
 3 1 6
 100000 1
 4
 */