#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <stack>
using namespace std;
#define MAXN 1024
#define MAXM 32767
#define INF 1LL<<60
struct Node {
    Node *l, *r;
    vector< pair<long long, long long> > v;
    int kind;
    Node(Node *a = NULL, Node *b = NULL, int k = 0) {
        l = a, r = b, kind = k;
        v.clear();
    }
} nodes[MAXM];
bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second != b.second)
        return a.second < b.second;
    return a.first < b.first;
}
void dfs(Node *u) {
    if (u->l == NULL && u->r == NULL)
        return ;
    dfs(u->l);
    dfs(u->r);
    Node *lson = u->l, *rson = u->r;
    long long w, h;
    long long rmin = INF, lmin = INF;
    if (u->kind) {
        sort(lson->v.begin(), lson->v.end());
        sort(rson->v.begin(), rson->v.end());
        for (int i = 0, j = 0; i < lson->v.size(); i++) {
            while (j < rson->v.size() && rson->v[j].first <= lson->v[i].first)
                rmin = min(rmin, rson->v[j].second), j++;
            if (rmin == INF)    continue;
            w = lson->v[i].first;
            h = lson->v[i].second + rmin;
            u->v.push_back(make_pair(w, h));
        }
        for (int i = 0, j = 0; i < rson->v.size(); i++) {
            while (j < lson->v.size() && lson->v[j].first <= rson->v[i].first)
                lmin = min(lmin, lson->v[j].second), j++;
            if (lmin == INF)    continue;
            w = rson->v[i].first;
            h = rson->v[i].second + lmin;
            u->v.push_back(make_pair(w, h));
        }
    } else {
        sort(lson->v.begin(), lson->v.end(), cmp);
        sort(rson->v.begin(), rson->v.end(), cmp);
        for (int i = 0, j = 0; i < lson->v.size(); i++) {
            while (j < rson->v.size() && rson->v[j].second <= lson->v[i].second)
                rmin = min(rmin, rson->v[j].first), j++;
            if (rmin == INF)    continue;
            w = lson->v[i].first + rmin;
            h = lson->v[i].second;
            u->v.push_back(make_pair(w, h));
        }
        for (int i = 0, j = 0; i < rson->v.size(); i++) {
            while (j < lson->v.size() && lson->v[j].second <= rson->v[i].second)
                lmin = min(lmin, lson->v[j].first), j++;
            if (lmin == INF)    continue;
            w = rson->v[i].first + lmin;
            h = rson->v[i].second;
            u->v.push_back(make_pair(w, h));
        }
    }
    sort(u->v.begin(), u->v.end());
    u->v.resize(unique(u->v.begin(), u->v.end()) - u->v.begin());
}
int main() {
    int testcase, n, H[MAXN], W[MAXN], x;
    char s[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &H[i], &W[i]);
        }
        stack<Node*> stk;
        Node *p, *a, *b, *root;
        int size = 0;
        for (int i = 1; i < 2 * n; i++) {
            scanf("%s", s);
            if (s[0] == 'V' || s[0] == 'H') {
                p = &nodes[size++];
                b = stk.top(), stk.pop();
                a = stk.top(), stk.pop();
                *p = Node(a, b, s[0] == 'V');
                stk.push(p);
            } else {
                sscanf(s, "%d", &x);
                p = &nodes[size++];
                *p = Node(NULL, NULL);
                p->v.push_back(make_pair(H[x], W[x]));
                p->v.push_back(make_pair(W[x], H[x]));
                stk.push(p);
            }
        }
        root = stk.top();
        dfs(root);
        long long ret = INF;
        for (int i = 0; i < root->v.size(); i++)
            ret = min(ret, (long long) root->v[i].first * root->v[i].second);
        printf("%lld\n", ret);
    }
    return 0;
}
/*
 9999
 
 5
 1 5
 4 2
 3 3
 1 3
 5 4
 2 1 V 3 5 H 4 V H
 
 6
 4 2
 5 7
 7 2
 4 4
 1 4
 5 3
 2 3 H 1 5 V 6 4 H V V
 
 12
 2 5
 4 3
 4 2
 5 3
 2 4
 3 1
 2 6
 1 4
 4 2
 4 5
 7 8
 3 5
 1 2 H 3 4 H V 5 6 V H 7 8 H 9 10 H V 11 12 V H V
 
 3
 2 2
 3 1
 4 2
 3 1 2 H V
 
 24
 5 7
 1 3
 4 7
 3 2
 2 8
 1 1
 5 8
 1 2
 4 4
 3 2
 7 8
 1 1
 5 4
 1 2
 4 4
 5 2
 7 8
 1 1
 5 7
 1 2
 4 4
 3 2
 7 9
 1 1
 1 2 H 3 4 H V 5 6 V H 7 8 H 9 10 H V 11 12 V H V 13 14 H 15 16 H V 17 18 V H 19 20 H 21 22 H V 23 24 V H V H
 
 42
 2 3
 3 3
 4 2
 2 5
 4 4
 5 3
 4 4
 5 2
 3 7
 4 7
 3 3
 5 5
 3 3
 2 4
 5 2
 2 5
 4 4
 7 3
 2 3
 3 3
 4 2
 2 5
 4 4
 5 3
 4 4
 5 2
 3 7
 4 7
 3 3
 5 5
 3 3
 2 4
 5 2
 2 5
 4 4
 7 3
 2 6
 4 5
 7 8
 9 4
 3 1
 4 2
 8 4 9 V H 18 14 V H 2 17 V 11 V H 5 15 H 1 H 16 7 12 H V H 10 13 V 6 V 3 H V H 26 22 27 V H 36 32 V H 20 35 V 29 V H 23 33 H 19 H 34 25 30 H V H 28 31 V 24 V 21 H V H V 37 38 V 39 40 V H 41 42 H V H
 */