#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;
#define MAXBUF 8388608
struct Node {
    int lson, rson;
    long long sum;
} node[MAXBUF + 50];
int nodesize = 0;
int root[524288];
int build(int l, int r) {
    if (l > r)  return 0;
    int k = nodesize++;
    node[k].sum = 0;
    node[k].lson = node[k].rson = 0;
    if (l == r) return k;
    int m = (l + r)/2;
    node[k].lson = build(l, m);
    node[k].rson = build(m+1, r);
    return k;
}

int change(int p, int l, int r, int x, int val) {
    int k = nodesize++;
    node[k] = node[p];
    if (l == r) {
        node[k].sum = val;
        return k;
    }
    int m = (l + r)/2;
    if (x <= m)
        node[k].lson = change(node[p].lson, l, m, x, val);
    else
        node[k].rson = change(node[p].rson, m+1, r, x, val);
    node[k].sum = node[node[k].lson].sum + node[node[k].rson].sum;
    return k;
}

long long query(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y)
        return node[k].sum;
    int m = (l + r)/2;
    long long sum = 0;
    if (x <= m) {
        sum += query(node[k].lson, l, m, x, y);
    }
    if (y > m) {
        sum += query(node[k].rson, m+1, r, x, y);
    }
    return sum;
}
int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        
        root[0] = build(1, n);
        
        int pre_ver = 0, cmd, x = 0, y = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d %d", &cmd, &x);
            if (cmd == 0) {
                y = 0;
                root[i] = root[i - x - 1];
                pre_ver = i;
            } else if (cmd == 1) {
                scanf("%d", &y);
                root[i] = change(root[pre_ver], 1, n, x, y);
                pre_ver = i;
            } else if (cmd == 2){
                scanf("%d", &y);
//                printf("query root = %d\n", root[pre_ver]);
                printf("%lld\n", query(root[pre_ver], 1, n, x, y));
                root[i] = root[pre_ver];
                pre_ver = i;
            }
            if (nodesize > MAXBUF) {
                return 0;
            }
        }
    }
    return 0;
}
/*
 2 5
 1 1 1
 1 2 2
 2 1 2
 0 2
 2 1 2
 */

