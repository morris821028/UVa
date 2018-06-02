#include <bits/stdc++.h> 
using namespace std;

const int NUMPOS = 20000000;
const int INFPOS = 10000000;
const int MAXS = 1000000;
const int MAXN = 50005;

struct Stmt {
	int v[3];	// a = b+c, or a = b
	bool operator<(const Stmt &x) const {
		if (v[0] != x.v[0])	return v[0] < x.v[0];
		if (v[1] != x.v[1])	return v[1] < x.v[1];
		return v[2] < x.v[2];
	}
	bool operator==(const Stmt &x) const {
		return v[2] == x.v[2] && v[1] == x.v[1] && v[0] == x.v[0];
	}
	inline void init(int a, int b, int c) {
		v[0] = a, v[1] = b, v[2] = c;
	}
};

class AC {
public:
	static const int MAXNODE = 524288;
	static const int MAXSTACK = 131072;
	struct TNode;
	struct Node;
	struct TNode {
		Stmt key;
		Node *val;
		TNode *lson, *rson;
		void init() {
			val = NULL;
			lson = rson = NULL;
		}
	} tnodes[MAXNODE];
	static TNode *tnode_iter[MAXSTACK];
	struct TNodeIter {
		int size, index;
		TNodeIter(TNode *root) {
			size = 0, index = 0;
			dfs(root);
		}
		void dfs(TNode *u) {
			if (u == NULL)
				return ;
			tnode_iter[size++] = u;
			dfs(u->lson);
			dfs(u->rson);
		}
		TNode* next() {
			TNode *ret = NULL;
			if (index < size) {
				ret = tnode_iter[index];
				index++;
			}
			return ret;
		}
	};
	struct NodeBalancer {
		int index;
		void flatten(TNode *u) {
			if (u == NULL)
				return ;
			flatten(u->lson);
			tnode_iter[index++] = u;
			flatten(u->rson);
		}
		TNode* build(int l, int r) {
			if (l > r)
				return NULL;
			int m = (l+r)/2;
			TNode *u = tnode_iter[m];
			u->lson = build(l, m-1);
			u->rson = build(m+1, r);
			return u;
		}
	    void rebalance(Node *p) {
	    	TNode *root = p->next;
	    	index = 0;
	    	flatten(root);
	    	p->next = build(0, index-1);
		}
	} balancer;
    struct Node {
    	TNode *next;
        Node *fail;
        int val, id, dep;
        void init() {
            fail = NULL, next = NULL;
            val = 0, dep = 0;
            id = -1;
        }
    } nodes[MAXNODE];
    Node *root;
    int size, tsize;
    Node* getNode() {
        Node *p = &nodes[size++];
        assert(size < MAXNODE);
        p->init();
        return p;
    }
    TNode* newTNode() {
    	TNode *p = &tnodes[tsize++];
        assert(tsize < MAXNODE);
        p->init();
        return p;
	}
    void init() {
        size = 0, tsize = 0;
        root = getNode();
    }
    Node* &next(Node *p, const Stmt &stmt) {
    	TNode *root = p->next;
    	TNode *u;
    	if (root == NULL) {
    		u = newTNode();
    		u->key = stmt;
    		p->next = u;
    		return u->val;
		}
		int dep = 0;
		while (root != NULL) {
			if (root->key == stmt)
				return root->val;
			dep++;
			if (stmt < root->key) {
				if (root->lson != NULL) {
					root = root->lson;
				} else {
					u = newTNode();
		    		u->key = stmt;
		    		root->lson = u;
		    		goto done;
				}
			} else {
				if (root->rson != NULL) {
					root = root->rson;
				} else {
					u = newTNode();
		    		u->key = stmt;
		    		root->rson = u;
		    		goto done;
				}
			}
		}
		done:
		if (dep > 20)
			balancer.rebalance(p);
		return u->val;
	}
	Node* find(Node *p, const Stmt &stmt) {
    	TNode *root = p->next;
		while (root != NULL) {
			if (root->key == stmt)
				return root->val;
			if (stmt < root->key)
				root = root->lson;
			else
				root = root->rson;
		}
		return NULL;
	}
    int insert(Stmt str[], int n, int sid) {
        Node *p = root;
        for (int i = 0; i < n; i++) {
            Stmt &idx = str[i];
            Node* &q = next(p, idx);
            if (q == NULL) {
				q = getNode();
				q->dep = i+1;
			}
            p = q;
        }
        if (p->id < 0)
        	p->id = sid;
        return p->id;
    }
    void build() {
        queue<Node*> Q;
        Node *u, *p, *q;
        Q.push(root), root->fail = NULL;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            TNodeIter next_it(u->next);
            for (TNode *next = next_it.next(); next != NULL; next = next_it.next()) {
            	Stmt i = next->key;
            	Node *it;
            	q = next->val;
            	Q.push(q);
            	p = u->fail;
            	to_decidable(i, p);
            	while (p != NULL && (it = find(p, i)) == NULL) {
            		p = p->fail;
            		to_decidable(i, p);
            	}
            	if (p == NULL || it == NULL)
            		q->fail = root;
            	else
            		q->fail = it;
			}
        }
    }
	
	inline void to_decidable(Stmt &x, Node *u) {
		if (u == NULL)
			return ;
		int dep = u->dep*3;
		if (x.v[0] < NUMPOS && x.v[0] > dep)
			x.v[0] = INFPOS;
    	if (x.v[1] < NUMPOS && x.v[1] > dep+1)
    		x.v[1] = INFPOS;
    	if (x.v[2] < NUMPOS && x.v[2] > dep+2)
    		x.v[2] = INFPOS;
	}

	inline int hasNext(Stmt &x, Node *u) {
		return find(u, x) != NULL;
	}
    
    void query(Stmt str[], int n, int ret[], int tot) {
        Node *u = root;
        vector<Node*> q1, q2;
        q1.push_back(root);
        for (int i = 0; i < n; i++) {
        	q2.clear();
        	for (auto u : q1) {
        		Stmt idx = str[i];
            	int has = 0;
            	
            	to_decidable(idx, u);
				while (u != NULL && u != root && !hasNext(idx, u)) {
					u = u->fail;
					to_decidable(idx, u);
				}

				if (u == NULL) {
					u = root;
				} else {
					Node *v = NULL;
					to_decidable(idx, u);
					Node *u_next = find(u, idx);
					if (u_next != NULL) {
						has = 1;
						v = u_next;
					}

					Node *p = v;
		            while (p != NULL && p != root && p->val >= 0) {
		            	p->val = -1;
		            	if (p->id >= 0 && ret[p->id] < 0) {
		            		ret[p->id] = (i+1 - p->dep);
		            		tot--;
							if (tot == 0)
    							return ;
		            	}
		            	p = p->fail;
					}
					if (i+1 < n && v != NULL)
						q2.push_back(v);
				}
				if (i+1 < n && !has)
					q2.push_back(root);
			}
        	q1.swap(q2);
        }
    }
} ac;
AC::TNode *AC::tnode_iter[AC::MAXSTACK];

inline static int tokenizer(char s[], char *tok[]) {
	int m = 0, n = strlen(s);
	for (int i = 0; i < n; i++) {
		while (s[i] && s[i] == ' ')
			i++;
		tok[m] = s+i, m++;
		while (s[i] > ' ')
			i++;
		s[i] = '\0';
	}
	tok[m] = NULL;
	return m;
}

inline static int to_int(char s[]) {
	int x = 0;
	for (int i = 0; s[i]; i++)
		x = x*10 + s[i]-'0';
	return x;
}

struct TrieMap {
	static const int MAXC = 52;
	static const int MAXNODE = 65536;
	struct Node {
        Node *next[MAXC];
        int val;
        void init() {
        	val = 0;
            memset(next, 0, sizeof(next));
        }
    } nodes[MAXNODE];
    Node *root;	
    int size;
    void init() {
        size = 0;
        root = newNode();
    }
    Node* newNode() {
        Node *p = &nodes[size++];
        assert(size < MAXNODE);
        p->init();
        return p;
    }
    int toIndex(char c) {
    	if (c >= 'a')	return c-'a' + 26;
    	return c-'A';
	}
	int& insert(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = newNode();
            p = p->next[idx];
        }
        return p->val;
    }
} trie;

static int encode(char tok[], int &pos) {
	int a;
	pos++;
	if (tok[0] >= 'A') {
		int &pa = trie.insert(tok);
		if (pa == 0) 
			a = INFPOS;
		else
			a = pos - pa;
		pa = pos;
	} else {
		a = NUMPOS + to_int(tok);
	}
	return a;
}

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
static int bug_line = 0;
inline int ReadLine(char *s) {
	static char c;
	bug_line++;
	while ((c = readchar()) < ' ') {if(c == EOF) return 0;}
	*s = c, s++;
	while ((c = readchar()) >= ' ')
		*s = c, s++;
	*s = '\0';
}

int read_note(int m, Stmt stmts[]) {
	static char s[65536];
	static char *tok[1024];
	int pos = 0;
	trie.init();
	for (int i = 0; i < m; i++) {
//		fgets(s, 1024, stdin);
		ReadLine(s);
		int n = tokenizer(s, tok);
		int a, b, c;
		if (n == 3) {
			a = encode(tok[0], pos);
			b = encode(tok[2], pos);
			c = 0, pos++;
		} else if (n == 5) {
			a = encode(tok[0], pos);
			b = encode(tok[2], pos);
			c = encode(tok[4], pos);
		}
		stmts[i].init(a, b, c);
	}
} 

int main() {
	int testcase;
	int cases = 0;
	int offset = 0;
	static char line[131072];
//	scanf("%d", &testcase);
	ReadLine(line), testcase = atoi(line);
	while (testcase--) {
		int n, m;
//		scanf("%d", &n);
		ReadLine(line), n = atoi(line);

		static Stmt stmts[MAXS];
		static int pos[50005];
		static int ret[50005];

		ac.init();
		int tot = 0;
		for (int i = 0; i < n; i++) {
//			scanf("%d", &m); while (getchar() != '\n');
			ReadLine(line), m = atoi(line);
			read_note(m, stmts);
			
			int pid = ac.insert(stmts, m, i);
			tot += pid == i;
			ret[i] = -1;
			pos[i] = pid;
		}
		ac.build();

//		scanf("%d", &m); while (getchar() != '\n');
		ReadLine(line), m = atoi(line);
		read_note(m, stmts);
		ac.query(stmts, m, ret, tot);

		for (int i = 0; i < n; i++) {
			int r = ret[pos[i]];
			if (r >= 0)
				printf("%d\n", r+1);
			else
				puts("NONE");
		}
	}
	return 0;
}
/*
2
3
4
bed = 100
table = 150
furniture = bed + table
furniture = furniture + 10
1
beer = 100
2
a = a + a
a = a + 10
10
furniture = 100
table = 150
furniture = furniture + table
furniture = furniture + 10
sofa = 100
stol = 150
meble = sofa + stol
meble = meble + 10
picie = 100
drink = 0100

3
2
1
a = 100 + 200
1
a = 100
2
x = 100 + 200
y = 100

1
2
3
a = 0
a = 0
b = 0
3
a = 0
b = 0
a = 0
0 
*/
