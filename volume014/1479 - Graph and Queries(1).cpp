#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAXN 65536
#define MAXM 65536
#define MAXQ (1<<20)
struct node;
node *null;
struct node {
    node *lson, *rson;
    int key, value, size;
    
    node(int x = 0, int s = 1):key(x), size(s) {
        lson = rson = null;
    }
    void update() {
        if (this != null)
            size = lson->size + rson->size + 1;
    }
} nodes[MAXQ], *root[MAXN];
struct treap {
    int bufIdx;
    node *getNode(int val) {
        node *ret = &nodes[bufIdx++];
        *ret = node(val);
        ret->value = rand();
        return ret;
    }
    void rotate(node* &a, int dir) { // dir {0: left, 1: right}
        node *p;
        if (dir == 0) {
            p = a->rson;
            a->rson = p->lson;
            p->lson = a;
        } else {
            p = a->lson;
            a->lson = p->rson;
            p->rson = a;
        }
        a->update(), p->update();
        a = p;
    }
    void insert(node* &a, int val) {
        if (a == null)
            a = getNode(val);
        else {
            if (val < a->key) {
                insert(a->lson, val);
                if (a->lson->value > a->value)
                    rotate(a, 1);
            } else {
                insert(a->rson, val);
                if (a->rson->value > a->value)
                    rotate(a, 0);
            }
        }
        a->update();
    }
    void remove(node* &a, int val) {
        if (a->key == val) {
            if (a->lson == null)
                a = a->rson;
            else if (a->rson == null)
                a = a->lson;
            else {
                if (a->lson->value > a->rson->value)
                    rotate(a, 1), remove(a->rson, val);
                else
                    rotate(a, 0), remove(a->lson, val);
            }
        } else if (val < a->key) {
            remove(a->lson, val);
        } else {
            remove(a->rson, val);
        }
        a->update();
    }
    void merge(node* &from, node* &to) {
        if (from->lson != null)
            merge(from->lson, to);
        if (from->rson != null)
            merge(from->rson, to);
        insert(to, from->key); // delete node `from`, need use delete replace pool.
    }
    node* kth_element(node* &a, int k) {
        if (a == null || k <= 0 || k > a->size)	return null;
        if (k == a->lson->size + 1)
            return a;
        if (k <= a->lson->size)
            return kth_element(a->lson, k);
        else
            return kth_element(a->rson, k - a->lson->size - 1);
    }
    node* rkth_element(node* &a, int k) {
        if (a == null || k <= 0 || k > a->size)	return null;
        if (k == a->rson->size + 1)
            return a;
        if (k <= a->rson->size)
            return rkth_element(a->rson, k);
        else
            return rkth_element(a->lson, k - a->rson->size - 1);
    }
    int lower_dist(node* &a, int val) {
        if (a == null)	return 1;
        if (a->value < val)
            return a->lson->size + 1 + lower_dist(a->rson, val);
        else
            return lower_dist(a->lson, val);
    }
    int upper_dist(node* &a, int val) {
        if (a == null)	return 1;
        if (a->value > val)
            return a->rson->size + 1 + upper_dist(a->lson, val);
        else
            return upper_dist(a->rson, val);
    }
    void print(node *ver) {
        if (ver == null)	return;
        print(ver->lson);
        printf("print %d %d\n", ver->key, ver->size);
        print(ver->rson);
    }
    void init() {
        bufIdx = 0;
        null = &nodes[bufIdx++];
        null->size = 0, null->lson = null->rson = null, null->value = 0;
    }
} tree;

char cmd[MAXQ][4];
int QX[MAXQ], QY[MAXQ], edgeX[MAXM], edgeY[MAXM], w[MAXN];

int parent[MAXN], weight[MAXN];
int findp(int x) {
    return parent[x] == x ? x : (parent[x] = findp(parent[x]));
}
void joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y)	return;
    if (weight[x] > weight[y]) {
        parent[y] = x, weight[x] += weight[y];
        tree.merge(root[y], root[x]);
        
    } else {
        parent[x] = y, weight[y] += weight[x];
        tree.merge(root[x], root[y]);
    }
}
void initDisjointSet(int n)  {
    for (int i = 1; i <= n; i++)
        parent[i] = i, weight[i] = 1;
}
void changeVertex(int u, int val) {
    int r = findp(u);
    tree.remove(root[r], w[u]);
    tree.insert(root[r], val);
    w[u] = val;
}
int main() {
    //    freopen("in.txt", "r+t", stdin);
    //    freopen("out.txt", "w+t", stdout);
    int n, m, q, t;
    int cases = 0;
    while (scanf("%d %d", &n, &m) == 2 && n) {
        tree.init();
        for (int i = 1; i <= n; i++)
            scanf("%d", &w[i]);
        for (int i = 1; i <= m; i++)
            scanf("%d %d", &edgeX[i], &edgeY[i]);
        int exists[MAXM] = {};
        for (int i = 1; i <= m; i++)
            exists[i] = 1;
        for (q = 0; scanf("%s", cmd[q]) == 1 && cmd[q][0] != 'E'; q++) {
            if (cmd[q][0] == 'D')
                scanf("%d", &QX[q]), exists[QX[q]] = 0;
            else if (cmd[q][0] == 'C')
                scanf("%d %d", &QX[q], &QY[q]), t = QY[q], QY[q] = w[QX[q]], w[QX[q]] = t;
            else if (cmd[q][0] == 'Q')
                scanf("%d %d", &QX[q], &QY[q]);
        }
        
        for (int i = 1; i <= n; i++)
            root[i] = null;
        for (int i = 1; i <= n; i++)
            tree.insert(root[i], w[i]);
        initDisjointSet(n);
        for (int i = 1; i <= m; i++)
            if (exists[i] == 1)
                joint(edgeX[i], edgeY[i]);
        
        double ret = 0, cnt = 0;
        for (int i = q - 1; i >= 0; i--) {
            if (cmd[i][0] == 'D')
                joint(edgeX[QX[i]], edgeY[QX[i]]);
            else if (cmd[i][0] == 'C')
                changeVertex(QX[i], QY[i]);
            else if (cmd[i][0] == 'Q') {
                cnt++;
                node* v = tree.rkth_element(root[findp(QX[i])], QY[i]);
                if (v == null)	/*puts("undefined")*/;
                else 			ret += v->key/*, printf("kth %d\n", v->key)*/;
            }
        }
        ret /= cnt;
        printf("Case %d: %lf\n", ++cases, ret);
    }
    return 0;
}
/*
 3 3
 10
 20
 30
 1 2
 2 3
 1 3
 D 3
 Q 1 2
 Q 2 1
 D 2
 Q 3 2
 C 1 50
 Q 1 1
 E
 */
