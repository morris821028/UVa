#include <bits/stdc++.h>
using namespace std;
#define MAXN 7100000
#define MAXQ 60005

class PersistentTreap {
public:
    struct Node;
    static Node *null;
    struct Node {
        Node *lson, *rson;
        int key, size;
        long long val, mnval, mxval, sumval;
        long long adel; // delivery
        int rdel;
        
        Node(long long c = 0, int s = 1): size(s) {
            lson = rson = null;
            key = rand();
            val = mnval = mxval = sumval = c;
            adel = rdel = 0;
        }
        void update() {
            size = 1;
            size += lson->size + rson->size;
        }
        void pushUp() {
            mnval = mxval = sumval = val;
            if (lson != null) {
                mnval = min(mnval, lson->mnval + lson->adel);
                mxval = max(mxval, lson->mxval + lson->adel);
                sumval += lson->sumval + lson->adel * lson->size;
            }
            if (rson != null) {
                mnval = min(mnval, rson->mnval + rson->adel);
                mxval = max(mxval, rson->mxval + rson->adel);
                sumval += rson->sumval + rson->adel * rson->size;
            }
        }
        void pushDown(PersistentTreap &treap) {
            if (adel) {
                val += adel, mnval += adel, mxval += adel;
                if (lson != null) {
                	lson = treap.cloneNode(lson);
                    lson->adel += adel;
                }
                if (rson != null) {
                	rson = treap.cloneNode(rson);
                    rson->adel += adel;
                }
                adel = 0;
            }
            if (rdel&1) {
                if (lson == null)
                    lson = rson, rson = null;
                else if (rson == null)
                    rson = lson, lson = null;
                else
                    swap(lson, rson);
                
                if (lson != null) {
                	lson = treap.cloneNode(lson);
                    lson->rdel += rdel;
                } 
				if (rson != null) {
					rson = treap.cloneNode(rson);
                    rson->rdel += rdel;
                }
                rdel = 0;
            }
            pushUp();
        }
    } nodes[MAXN], *root[MAXQ];
    int bufIdx, verIdx;
    
    Node* merge(Node* a, Node* b) {
        if (a == null)	return cloneNode(b);
        if (b == null)	return cloneNode(a);
        if (a != null)	a->pushDown(*this);
    	if (b != null)	b->pushDown(*this);
        Node *ret;
        if (a->key < b->key) {
            ret = cloneNode(a);
            ret->rson = merge(a->rson, b);
        } else {
            ret = cloneNode(b);
            ret->lson = merge(a, b->lson);
        }
        ret->update();
        ret->pushUp();
        return ret;
    }
    void split(Node* a, Node* &l, Node* &r, int n) {
        if (n == 0) {
            l = null, r = cloneNode(a);
            return ;
        } 
		if (a->size <= n) {
            l = cloneNode(a), r = null;
            return ;
        }         
		if (a != null)
            a->pushDown(*this);
		if (a->lson->size >= n) {
            r = cloneNode(a);
            split(a->lson, l, r->lson, n);
            r->update();
            r->pushUp();
        } else {
            l = cloneNode(a);
            split(a->rson, l->rson, r, n - (a->lson->size) - 1);
            l->update();
            l->pushUp();
        }
    }
    
    void insert(Node* &a, Node *ver, int pos, long long s[], int sn) {
        Node *p, *q, *r;
        int n = sn;
        split(ver, p, q, pos);
        build(r, 0, n - 1, s);
        p = merge(p, r);
        a = merge(p, q);
    }
    void erase(Node* &a, Node *ver, int pos, int n) {
        Node *p, *q, *r;
        split(ver, p, q, pos - 1);
        split(q, q, r, n);
        a = merge(p, r);
    }
    void reverse(Node* &a, Node *ver, int left, int right) {
        Node *p, *q, *r;
        split(ver, p, q, left - 1);
        split(q, q, r, right - left + 1);
        q->rdel++;
        a = merge(p, q);
        a = merge(a, r);
    }
    void add(Node* &a, Node *ver, int left, int right, long long val) {
        Node *p, *q, *r;
        split(ver, p, q, left - 1);
        split(q, q, r, right - left + 1);
        q->adel += val;
        a = merge(p, q);
        a = merge(a, r);
    }
    long long q_sum, q_max, q_min;
    void q_dfs(Node *u, int left, int right) {
        left = max(left, 1);
        right = min(right, u->size);
        if (left > right)
            return;        
		if (u != null)
            u->pushDown(*this);
        int lsz = u->lson != null ? u->lson->size : 0;
        int rsz = u->rson != null ? u->rson->size : 0;

        if (left == 1 && right == lsz + rsz + 1) {
            q_sum += u->sumval;
            q_max = max(q_max, u->mxval);
            q_min = min(q_min, u->mnval);
            return ;
        }
        if (left <= lsz+1 && lsz+1 <= right) {
            q_sum += u->val;
            q_max = max(q_max, u->val);
            q_min = min(q_min, u->val);
        }
        
        if (u->lson != null && left <= lsz)
            q_dfs(u->lson, left, right);
        if (u->rson != null && right > lsz+1)
            q_dfs(u->rson, left - lsz - 1, right - lsz - 1);
    }
    void q_init() {
        q_max = LONG_LONG_MIN;
        q_min = LONG_LONG_MAX;
        q_sum = 0;
    }
    long long findMax(Node *ver, int left, int right) {
        q_init();
        q_dfs(ver, left, right);
        return q_max;
    }
    long long findMin(Node *ver, int left, int right) {
        q_init();
        q_dfs(ver, left, right);
        return q_min;
    }
    long long findSum(Node *ver, int left, int right) {
        q_init();
        q_dfs(ver, left, right);
        return q_sum;
    }
    void print(Node *ver) {
        if (ver == null)	return;
        ver->pushDown(*this);
        print(ver->lson);
        printf("[%3lld]", ver->val);
        print(ver->rson);
    }
    void init() {
        bufIdx = verIdx = 0;
        root[verIdx] = null;
    }
private:
    Node* cloneNode(Node* u) {
        Node *ret;
        if (u == null) {
            return u;
        } else {
        	if (bufIdx >= MAXN)
        		exit(0);
            assert(bufIdx < MAXN);
            ret = &nodes[bufIdx++];
            *ret = *u;
            return ret;
        }
    }
    void build(Node* &a, int l, int r, long long s[]) {
        if (l > r)	return ;
        int m = (l + r) /2;
        Node u = Node(s[m]), *p = &u, *q;
        a = cloneNode(p), p = null, q = null;
        build(p, l, m-1, s);
        build(q, m+1, r, s);
        p = merge(p, a);
        a = merge(p, q);
        a->update();
        a->pushUp();
    }
} tree;
PersistentTreap::Node t(0, 0);
PersistentTreap::Node *PersistentTreap::null = &t;
int main() {
    int N, Q;
    long long A[65536];
    long long cmd, x, y, v;
    while (scanf("%d", &N) == 1) {
        for (int i = 1; i <= N; i++)
            scanf("%lld", &A[i]);
        tree.init();
        tree.insert(tree.root[0], tree.null, 0, A+1, N);
        scanf("%d", &Q);
        int verIdx = 0;
        long long encrypt = 0, ret = 0;
        for (int i = 1; i <= Q; i++) {
            scanf("%lld", &cmd);
            cmd ^= encrypt;
            if (cmd == 1) { 		// insert
                scanf("%lld %lld", &x, &v);
                x ^= encrypt, v ^= encrypt;
                long long B[] = {v};
                tree.insert(tree.root[i], tree.root[verIdx], (int) x, B, 1);
                verIdx = i;
            } else if (cmd == 2) { 	// erase
                scanf("%lld", &x);
                x ^= encrypt;
                tree.erase(tree.root[i], tree.root[verIdx], (int) x, 1);
                verIdx = i;
            } else if (cmd == 3) { 	// reverse
                scanf("%lld %lld", &x, &y);
                x ^= encrypt, y ^= encrypt;
                tree.reverse(tree.root[i], tree.root[verIdx], (int) x, (int) y);
                verIdx = i;
            } else if (cmd == 4) { 	// [x, y] += v
                scanf("%lld %lld %lld", &x, &y, &v);
                x ^= encrypt, y ^= encrypt, v ^= encrypt;
                tree.add(tree.root[i], tree.root[verIdx], (int) x, (int) y, v);
                verIdx = i;
            } else if (cmd == 5) {  // max(A[x:y])
                scanf("%lld %lld", &x, &y);
                x ^= encrypt, y ^= encrypt;
                ret = tree.findMax(tree.root[verIdx], (int) x, (int) y);
                printf("%lld\n", ret);
                encrypt = ret;
                tree.root[i] = tree.root[verIdx];
                verIdx = i;
            } else if (cmd == 6) {  // min(A[x:y])
                scanf("%lld %lld", &x, &y);
                x ^= encrypt, y ^= encrypt;
                ret = tree.findMin(tree.root[verIdx], (int) x, (int) y);
                printf("%lld\n", ret);
                encrypt = ret;
                tree.root[i] = tree.root[verIdx];
                verIdx = i;
            } else if (cmd == 7) {  // sum(A[x:y])
                scanf("%lld %lld", &x, &y);
                x ^= encrypt, y ^= encrypt; 
                ret = tree.findSum(tree.root[verIdx], (int) x, (int) y);
                printf("%lld\n", ret);
                encrypt = ret;
                tree.root[i] = tree.root[verIdx];
                verIdx = i;
            } else if (cmd == 0) {  // back Day x-th
                scanf("%lld", &x);
                x ^= encrypt;
                tree.root[i] = tree.root[x];
                verIdx = i;
            } else {
                puts("WTF");
                return 0;
            }
        }
    }
    return 0;
}

