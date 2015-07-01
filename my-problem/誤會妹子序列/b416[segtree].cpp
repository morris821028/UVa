#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

const int MAXNODE = 3000000;
const int MAXN = 100005;
const int MAXQ = 100005;
class SegementTree {
public:
    struct Node {
        Node *lson, *rson;
        int val;
    } nodes[MAXNODE];
    int nodesize, L, R;
    Node* init(int l, int r) {
        nodesize = 0;
        L = l, R = r;
        Node* root = build(l, r);
        return root;
    }
    Node* newNode() {
        if (nodesize >= MAXNODE)
            exit(0);
        return &nodes[nodesize++];
    }
    Node* cloneNode(Node *p) {
        if (nodesize >= MAXNODE)
            exit(0);
        Node* u = &nodes[nodesize++];
        *u = *p;
        return u;
    }
    Node* build(int l, int r) {
        if (l > r)  return NULL;
        Node *u = newNode();
        u->lson = u->rson = NULL;
        if (l == r) {
            u->val = 0;
        } else {
            int m = (l + r)/2;
            u->lson = build(l, m);
            u->rson = build(m+1, r);
        }
        return u;
    }
    Node* add(Node *p, int x, int val) {
        return add(p, x, val, L, R);
    }
    int query(Node *tp, Node *tq, int x, int y) {
        return query(tp, tq, L, R, x, y);
    }
private:
    Node* add(Node *p, int x, int val, int l, int r) {
        Node *u = cloneNode(p);
        u->val += val;
        if (l == r) {
            return u;
        } else {
            int mid = (l + r)/2;
            if (x <= mid)
                u->lson = add(p->lson, x, val, l, mid);
            else
                u->rson = add(p->rson, x, val, mid+1, r);
        }
        return u;
    }
    int query(Node *tp, Node *tq, int l, int r, int x, int y) {
        if (x <= l && r <= y)
            return tq->val - tp->val;
        int mid = (l+r)/2;
        if (y <= mid)
            return query(tp->lson, tq->lson, l, mid, x, y);
        else if (x > mid)
            return query(tp->rson, tq->rson, mid+1, r, x, y);
        else
            return query(tp->lson, tq->lson, l, mid, x, mid) +
                query(tp->rson, tq->rson, mid+1, r, mid+1, y);
    }
} segTree;

namespace mLocalStream {
    inline int readchar() {
        const int N = 1048576;
        static char buf[N];
        static char *p = buf, *end = buf;
        if(p == end) {
            if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
            p = buf;
        }
        return *p++;
    }
    inline int ReadInt(int *x) {
        static char c, neg;
        while((c = readchar()) < '-')    {if(c == EOF) return 0;}
        neg = (c == '-') ? -1 : 1;
        *x = (neg == 1) ? c-'0' : 0;
        while((c = readchar()) >= '0')
            *x = (*x << 3) + (*x << 1) + c-'0';
        *x *= neg;
        return 1;
    }
    class Print {
    public:
        static const int N = 1048576;
        char buf[N], *p, *end;
        Print() {
            p = buf, end = buf + N - 1;
        }
        void printInt(int x) {
            static char stk[16];
            int idx = 0;
            stk[idx++] = '\n';
            if (!x)
                stk[idx++] = '0';
            while (x)
                stk[idx++] = x%10 + '0', x /= 10;
            while (idx) {
                if (p == end) {
                    *p = '\0';
                    printf("%s", buf), p = buf;
                }
                *p = stk[--idx], p++;
            }
        }
        ~Print() {
            *p = '\0';
            printf("%s", buf);
        }		
    } bprint;
}

SegementTree::Node *ver[MAXQ];
pair<int, int> A[MAXN];
int fver[MAXN];
int main() {
    int n, m, x;
    while (mLocalStream::ReadInt(&n)) {
        mLocalStream::ReadInt(&m);
        for (int i = 1; i <= n; i++)
            mLocalStream::ReadInt(&x), A[i] = make_pair(x, i);
        sort(A+1, A+n+1);
        
        ver[0] = segTree.init(1, n);
        for (int i = 1; i <= n; i++) {
            ver[i] = segTree.add(ver[i-1], A[i].second, 1);
            fver[i] = A[i].first;
        }
        for (int i = 0; i < m; i++) {
            int l, r, a, b;
            mLocalStream::ReadInt(&l);
            mLocalStream::ReadInt(&r);
            mLocalStream::ReadInt(&a);
            mLocalStream::ReadInt(&b);
            int va = (int) (lower_bound(fver+1, fver+n+1, a) - fver) - 1;
            int vb = (int) (upper_bound(fver+1, fver+n+1, b) - fver) - 1;
            mLocalStream::bprint.printInt(segTree.query(ver[va], ver[vb], l, r));
        }
    }
    return 0;
}
/*
 10 10
 4 4 5 1 4 1 5 1 2 1
 5 9 1 2
 3 4 7 9
 4 4 2 5
 2 3 4 7
 5 10 4 4
 3 9 1 1
 1 4 5 9
 8 9 3 3
 2 2 1 6
 8 9 1 4
*/