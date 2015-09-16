#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
const int MAXN = 262144;
int tree[MAXN], A[MAXN];
vector<int> T, g[MAXN];
int validInput(int n) {
    for (int i = 0; i < T.size(); i++) {
        if (T[i] >= n || T[i] < 0)
            return 0;
    }
    return 1;
}
void build(int k, int l, int r) {
    if (l == r) {
        tree[k] = A[l] != 0;
        return ;
    }
    int mid = (l + r)/2;
    build(k<<1, l, mid);
    build(k<<1|1, mid+1, r);
    tree[k] = tree[k<<1] + tree[k<<1|1];
}
int fetch(int k, int l, int r) {
    if (l == r)
        return l;
    int mid = (l + r)/2;
    if (tree[k<<1] <= mid - l)
        return fetch(k<<1, l, mid);
    else
        return fetch(k<<1|1, mid+1, r);
}
void remark(int k, int l, int r, int x) {
    if (l == r) {
        tree[k] = A[l] != 0;
        return ;
    }
    int mid = (l + r)/2;
    if (x <= mid)
        remark(k<<1, l, mid, x);
    else
        remark(k<<1|1, mid+1, r, x);
    tree[k] = tree[k<<1] + tree[k<<1|1];
}
void solve(int n) {
    int u, v;
    for (int i = 0; i < n; i++)
        A[i] = 0, g[i].clear();
    for (int i = 0; i < T.size(); i++)
        A[T[i]]++;
    build(1, 0, n-1);
    for (int i = 0; i < T.size(); i++) {
        v = fetch(1, 0, n-1);
        if (A[v]) {
            puts("impossible");
            return ;
        }
        g[T[i]].push_back(v), g[v].push_back(T[i]);
        A[T[i]]--, A[v]++;
        remark(1, 0, n-1, v);
        remark(1, 0, n-1, T[i]);
    }
    v = fetch(1, 0, n-1);
    if (A[v]) {
        puts("impossible");
        return ;
    }
    A[v]++, remark(1, 0, n-1, v);
    u = fetch(1, 0, n-1);
    if (A[u]) {
        puts("impossible");
        return ;
    }
    A[u]++, remark(1, 0, n-1, u);
    g[u].push_back(v), g[v].push_back(u);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
        for (int j = 0; j < g[i].size(); j++) {
            printf("%d%c", g[i][j], j == g[i].size()-1 ? '\n' : ' ');
        }
    }
}
int main() {
    int cases = 0;
    string line;
    int x, n;
    while (getline(cin, line)) {
        if (cases++)    puts("*");
        stringstream sin(line);
        T.clear();
        while (sin >> x)
            T.push_back(x);
        n = (int) T.size()+2;
        if (!validInput(n)) {
            puts("impossible");
            continue;
        }
        solve(n);
    }
    return 0;
}