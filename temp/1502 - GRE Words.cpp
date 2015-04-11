// NOTES: has error test data, there are some characters which aren't lowercase letters.
// FUCK
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
#include <assert.h>
#include <assert.h>
#pragma comment( linker, "/STACK:1024000000,1024000000")
using namespace std;

const int MAXCHAR = 26;
const int MAXNODE = 1048576;

class ACmachine {
public:
    struct Node {
        Node *next[MAXCHAR], *fail;
        int cnt, val, id, nid;
        void init() {
            fail = NULL;
            cnt = val = 0;
            nid = id = -1;
            memset(next, 0, sizeof(next));
        }
    } nodes[MAXNODE];
    Node *root;
    int size;
    vector<int> fg[MAXNODE];
    Node* getNode() {
        Node *p = &nodes[size++];
        p->init(), p->nid = size-1;
        assert(size < MAXNODE);
        fg[p->nid].clear();
        return p;
    }
    void init() {
        size = 0;
        root = getNode();
    }
    int toIndex(char c) {
    	assert(c - 'a' >= 0 && c - 'a' < MAXCHAR);
        return c - 'a';
    }
    void dfs(Node *p, Node *q) {
        for (int i = 0; i < MAXCHAR; i++) {
            if (q->next[i]) {
                Node *u = p->next[i], *v = q->next[i];
                if (u == NULL)
                    p->next[i] = getNode(), u = p->next[i];
                u->cnt |= v->cnt;
                dfs(u, v);
            }
        }
    }
    void merge(const ACmachine &other) {
        dfs(root, other.root);
    }
    void insert(const char str[], int sid) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        p->cnt = 1;
        if (sid >= 0)	p->id = sid;
    }
    int find(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        return p->cnt;
    }
    void build() { // AC automation    
        queue<Node*> Q;
        Node *u, *p;
        Q.push(root), root->fail = NULL;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            if (u != root) {
            	assert(u->fail != NULL);
            	assert(u->nid != u->fail->nid);
            	fg[u->nid].push_back(u->fail->nid);
            	fg[u->fail->nid].push_back(u->nid);
            }
            for (int i = 0; i < MAXCHAR; i++) {
                if (u->next[i] == NULL)
                    continue;
                Q.push(u->next[i]);
                p = u->fail;
                while (p != NULL && p->next[i] == NULL)
                    p = p->fail;
                if (p == NULL || p->next[i] == NULL)
                    u->next[i]->fail = root;
                else
                    u->next[i]->fail = p->next[i];
                u->next[i]->val = u->next[i]->fail->val + u->next[i]->cnt;
                u->next[i]->id = u->next[i]->fail->id | u->next[i]->id;
            }
        }
    }
    int query(const char str[]) {
        Node *u = root, *p;
        int matched = 0;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            while (u->next[idx] == NULL && u != root)
                u = u->fail;
            u = u->next[idx];
            u = (u == NULL) ? root : u;
            p = u;
            matched += p->val;
        }
        return matched;
    }
    void free() {
        return ;
        // owner memory pool version
        queue<Node*> Q;
        Q.push(root);
        Node *u;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = 0; i < MAXCHAR; i++) {
                if (u->next[i] != NULL) {
                    Q.push(u->next[i]);
                }
            }
            delete u;
        }
    }
};

const int MAXN = 1048576;
class SegmentTree {
public:
	struct Node {
		long long mx;
		pair<int, long long> label;
		void init() {
			mx = -1LL<<60;
			label = make_pair(0, 0);
		}
	} nodes[MAXN];
	void pushDown(int k, int l, int r) {
		int mid = (l + r)/2;
		if (nodes[k].label.first) {
			maxUpdate(k<<1, l, mid, nodes[k].label.second);
			maxUpdate(k<<1|1, mid+1, r, nodes[k].label.second);
			nodes[k].label = make_pair(0, 0); // cancel
		}
	}
	void pushUp(int k) {
		nodes[k].mx = max(nodes[k<<1].mx, nodes[k<<1|1].mx);
	}
	void build(int k, int l, int r) { 
		nodes[k].init();
		if (l == r) {
			nodes[k].mx = 0;
			return ;
		}
		int mid = (l + r)/2;
		build(k<<1, l, mid);
		build(k<<1|1, mid+1, r);
		pushUp(k);
	} 
	// operator, assign > add
	void maxUpdate(int k, int l, int r, long long val) {
		if (nodes[k].label.first)
			val = max(val, nodes[k].label.second);
		nodes[k].label = make_pair(1, val);
		nodes[k].mx = max(nodes[k].mx, val);
	}
	void assign(int k, int l, int r, int x, int y, int val) {
		if (x <= l && r <= y) {
			maxUpdate(k, l, r, val);
			return;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			assign(k<<1, l, mid, x, y, val);
		if (y > mid)
			assign(k<<1|1, mid+1, r, x, y, val);
		pushUp(k);
	}
	// query 
	long long r_mx;
	void qinit() {
		r_mx = -1LL<<60;
	}
	void query(int k, int l, int r, int x, int y) {
		if (x <= l && r <= y) {
			r_mx = max(r_mx, nodes[k].mx);
			return ;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			query(k<<1, l, mid, x, y);
		if (y > mid)
			query(k<<1|1, mid+1, r, x, y);
	}
};

ACmachine ac;
SegmentTree tree;
vector<string> words;
vector<int> wvals;

char s[1048576];
int bPos[MAXN], ePos[MAXN], inIdx;
void prepare(int u, int p) {
	bPos[u] = ++inIdx;
	for (int i = 0; i < ac.fg[u].size(); i++) {
		if (ac.fg[u][i] == p)	continue;
		prepare(ac.fg[u][i], u);
	}
	ePos[u] = inIdx;
} 
void solve() {
	for (int i = 0; i < ac.size; i++)
		bPos[i] = ePos[i] = 0;
	inIdx = 0;
	for (int i = 0; i < ac.size; i++) {
		if (bPos[i] == 0) {
			prepare(i, -1); // interval [1, inIdx]
		}
	}
			
	assert(inIdx < MAXN/2);
	tree.build(1, 1, inIdx);
	
	long long ret = 0;
	for (int i = 0; i < words.size(); i++) {
		ACmachine::Node *u = ac.root;
		int idx;
		long long dpval = 0;
		for (int j = 0; j < words[i].length(); j++) {
			idx = ac.toIndex(words[i][j]);
			while (u->next[idx] == NULL && u != ac.root)
                u = u->fail;
            u = u->next[idx];
            u = (u == NULL) ? ac.root : u;
            
            tree.qinit();
            tree.query(1, 1, inIdx, bPos[u->nid], bPos[u->nid]);
            dpval = max(dpval, tree.r_mx);
		}
		dpval += wvals[i];
		tree.assign(1, 1, inIdx, bPos[u->nid], ePos[u->nid], dpval);
		ret = max(ret, dpval);
	}
	printf("%lld\n", ret);
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int testcase, cases = 0;
	int N, val;
	scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d", &N);
    	    	
       	ac.init();
       	words.clear(), wvals.clear();
       	for (int i = 0; i < N; i++) {
       		scanf("%s %d", s, &val);
       		ac.insert(s, i);
       		words.push_back(s), wvals.push_back(val);
       	}
       	
       	ac.build();
       	
       	printf("Case #%d: ", ++cases);
       	solve(); 
       	
        ac.free();
    }
    return 0;
}
/*
999

4
abbaaa 49
bba 41
ba 19
bbba 20

8
abbaaa 49
bba 41
ba 19
bbba 20
abbbabaaa 21
b 47
ababba 26
a 0

3
abaab 35
ab 9
abaabaaabbabababaaab 35

8
aabbbbbababbaaaab 14
abaabbaaaaaabbaabbba 13
babaaababaaaaabababa 17
abaab 35
ab 9
abaabaaabbabababaaab 35
bbbaaa 31
aabab 34

32
aa 19
bababbabbbaabaaaab 40
aabbbaaaaaa 48
ababaaabbabbbaabbb 38
a 42
bbbbbaabbbaa 10
baabbbababaab 41
aabbabbabba 28
baaab 3
aaaaaaaaa 15
bbbabbababaaabab 16
aab 18
baaab 2
abbbab 2
bababa 4
bbabbbbbaabbaaaababb 35
bbbaabba 34
bbbb 24
bbbb 17
babbbabbababababaa 9
ababaaaa 38
bbbb 3
bba 31
aabaabaaa 34
aabbbbbaababaa 41
aabbbaabbbabaababbbb 45
abbbaabbababab 37
ababbaabb 3
bbabbbbbaba 8
a 10
babbabaabbbbab 34
bbababaaaaaaaaa 5
 */

