#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

struct Node {
    int l, r, lson, rson;
    int sum;
} node[2097152];
int nodesize = 0;
int A[131072], B[131072], root[131072];
int build(int l, int r) {
    if (l > r)  return 0;
    int k = nodesize++;
    node[k].l = l, node[k].r = r, node[k].sum = 0;
    node[k].lson = node[k].rson = 0;
    if (l == r) return k;
    int m = (l + r)/2;
    node[k].lson = build(l, m);
    node[k].rson = build(m+1, r);
    return k;
}

int change(int p, int x, int val) {
    int k = nodesize++;
    node[k] = node[p];
    node[k].sum += val;
    if (node[k].l == node[k].r) return k;
    int m = (node[k].l + node[k].r)/2;
    if (x <= m)
        node[k].lson = change(node[p].lson, x, val);
    else
        node[k].rson = change(node[p].rson, x, val);
    return k;
}

int query(int tp, int tq, int k) {
    if (node[tp].l == node[tp].r)
        return node[tp].l;
    int t = node[node[tp].lson].sum - node[node[tq].lson].sum;
    if (k <= t)
        return query(node[tp].lson, node[tq].lson, k);
    else
        return query(node[tp].rson, node[tq].rson, k - t);
}
int main() {
    int n, m, x, y, k;
    while (scanf("%d %d", &n, &m) == 2) {
        map<int, int> R;
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i]), R[A[i]] = 0;
        
        int size = 0;
        for (map<int, int>::iterator it = R.begin(); it != R.end(); it++) {
            it->second = ++size;
            B[it->second] = it->first;        }
        
        nodesize = 1;
        root[0] = build(1, size);
        
        for (int i = 1; i <= n; i++) {
            A[i] = R[A[i]];
            root[i] = change(root[i-1], A[i], 1);
        }
        
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &k);
            printf("%d\n", B[query(root[y], root[x-1], k)]);
        }
    }
    return 0;
}
/*
 7 3
 1 5 2 6 3 7 4
 2 5 3
 4 4 1
 1 7 3
 */

