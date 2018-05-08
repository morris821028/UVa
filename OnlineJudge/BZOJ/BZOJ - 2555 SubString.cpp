#include <bits/stdc++.h>
using namespace std;
  
class LCT { // Link-Cut Tree
public:
    static const int MAXN = 1200005;
    struct Node;
    static Node *EMPTY;
    static Node _mem[MAXN];
    static int bufIdx;
    struct Node {
        Node *ch[2], *fa;
        int lazy, size;
        void init() {
            ch[0] = ch[1] = fa = NULL;
            lazy = 0, size = 0;
        }
        bool is_root() {
            return fa->ch[0] != this && fa->ch[1] != this;
        }
        void pushdown() {
            if (lazy) {
                if (ch[0] != EMPTY)
                    ch[0]->lazy += lazy, ch[0]->size += lazy;
                if (ch[1] != EMPTY)
                    ch[1]->lazy += lazy, ch[1]->size += lazy;
                lazy = 0;
            }
        }
    };
    LCT() {
        EMPTY = &_mem[0];
        EMPTY->fa = EMPTY->ch[0] = EMPTY->ch[1] = EMPTY;
        EMPTY->size = 0;
        bufIdx = 1; 
    }
    void init() {
        bufIdx = 1;
    }
    Node* newNode() {
        Node *u = &_mem[bufIdx++];
        u->init();
        u->fa = u->ch[0] = u->ch[1] = EMPTY;
        return u;
    }
    void rotate(Node *x) {
        Node *y;
        int d;
        y = x->fa, d = y->ch[1] == x ? 1 : 0;
        x->ch[d^1]->fa = y, y->ch[d] = x->ch[d^1];
        x->ch[d^1] = y;
        if (!y->is_root())
            y->fa->ch[y->fa->ch[1] == y] = x;
        x->fa = y->fa, y->fa = x;
    }
    void deal(Node *x) {
        if (!x->is_root())   deal(x->fa);
        x->pushdown();
    }
    void splay(Node *x) {
        Node *y, *z;
        deal(x);
        while (!x->is_root()) {
            y = x->fa, z = y->fa;
            if (!y->is_root()) {
                if (y->ch[0] == x ^ z->ch[0] == y)
                    rotate(x);
                else
                    rotate(y);
            }
            rotate(x);
        }
    }
    Node* access(Node *u) {
        Node *v = EMPTY;
        for (; u != EMPTY; u = u->fa) {
            splay(u);
            u->ch[1] = v;
            v = u;
        }
        return v;
    }
    void mk_root(Node *u) {
        access(u), splay(u);
    }
    void cut(Node *x) {
        mk_root(x);
        x->ch[0]->size -= x->size;
        x->ch[0]->lazy -= x->size;
        x->ch[0] = x->ch[0]->fa = EMPTY;
    }
    void link(Node *x, Node *y) {
        x->fa = y;
        mk_root(y);
        y->size += x->size, y->lazy += x->size;
    }
  
    void cut(int x) {
        cut(_mem+x);
    }
    void link(int x, int y) {
        link(_mem+x, _mem+y);
    }
    void splay(int x) {
        splay(_mem+x);
    }
    void set(int x, int val) {
        _mem[x].size = val;
    }
    int get(int x) {
        return _mem[x].size;
    }
} lct;
LCT::Node *LCT::EMPTY, LCT::_mem[LCT::MAXN];
int LCT::bufIdx;
  
class SuffixAutomaton {
public:
    static const int MAXN = 1200000;
    static const int MAXC = 26;
    struct Node {
        Node *next[2], *fail;
        int step;
        void init() {
            fail = NULL, step = 0;
            memset(next, 0, sizeof(next));
        }
    } _mem[MAXN];
    int size;
    int n;
    Node *root, *tail;  
    LCT *lct;
    void init(LCT *tree) {
        size = 1;
        lct = tree;
        lct->init();     
        root = tail = newNode();
        n = 0;
    }
    Node* newNode() {
        lct->newNode();
        Node *p = &_mem[size++];
        p->init();
        return p;
    }
    Node* newNode(Node *q) {
        lct->newNode();
        Node *p = &_mem[size++];
        p->step = q->step, p->fail = q->fail;
        memcpy(p->next, q->next, sizeof(p->next));
        return p;
    }
    int toIndex(char c) { return c - 'A'; }
    void add(char c, int len) {
        c = toIndex(c);
        Node *p, *q, *np, *nq;
        p = tail, np = newNode();
        np->step = len;
        lct->set(np-_mem, 1);
        for (; p && p->next[c] == NULL; p = p->fail)
            p->next[c] = np;
        tail = np;
        if (p == NULL) {
            np->fail = root;
            lct->link(np-_mem, root-_mem);
        } else {
            if (p->next[c]->step == p->step+1) {
                np->fail = p->next[c];
                lct->link(np-_mem, p->next[c]-_mem);
            } else {
                q = p->next[c], nq = newNode(q);
                nq->step = p->step + 1;
                q->fail = np->fail = nq;
                lct->link(nq-_mem, nq->fail-_mem);
                lct->cut(q-_mem);
                lct->link(q-_mem, nq-_mem), lct->link(np-_mem, nq-_mem);
                for (; p && p->next[c] == q; p = p->fail)
                    p->next[c] = nq;
            }
        }
    }
    int append(const char *s) {
        for (int i = 0; s[i]; i++)
            add(s[i], ++n);
        return n;
    }
    int count(const char *s) {
        Node *p = root;
        for (int i = 0; s[i]; i++) {
            char c = toIndex(s[i]);
            if (p->next[c])
                p = p->next[c];
            else
                return 0;
        }
        lct->splay(p-_mem);
        return lct->get(p-_mem);
    }
} SAM;
  
int decode(char s[], int mask) {  
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        mask = (mask*131+i)%n;
        swap(s[i], s[mask]);
    }
    return n;
}  
  
int main() {
    static char s[1200005], cmd[16];
    int q, n;
    SAM.init(&lct);
    while (scanf("%d", &q) == 1) {
        scanf("%s", s);
        int n = SAM.append(s);
        int mask = 0;
        for (int i = 0; i < q; i++) {
            scanf("%s %s", cmd, s);
            decode(s, mask);
            if (cmd[0] == 'A') {
                SAM.append(s);
            } else {
                int ret = SAM.count(s);
                printf("%d\n", ret);
                mask ^= ret;
            }
        }
    }
    return 0;
}
/*
2
A
QUERY B
ADD BBABBBBAAB
  
2
AB
ADD BBABB
QUERY BB
*/
