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
		return v[0] == x.v[0] && v[1] == x.v[1] && v[2] == x.v[2];
	}
	void init(int a, int b, int c) {
		v[0] = a, v[1] = b, v[2] = c;
	}
};

class AC {
public:
	static const int MAXNODE = 1048576;
    struct Node {
    	map<Stmt, Node*> next;
        Node *fail;
        int val, id, dep;
        void init() {
            fail = NULL;
            val = 0;
            id = -1;
            dep = 0;
            next.clear();
        }
    } nodes[MAXNODE];
    Node *root;
    int size;
    Node* getNode() {
        Node *p = &nodes[size++];
        assert(size < MAXNODE);
        p->init();
        return p;
    }
    void init() {
        size = 0;
        root = getNode();
    }
    int insert(Stmt str[], int n, int sid) {
        Node *p = root;
        for (int i = 0; i < n; i++) {
            Stmt idx = str[i];
            Node* &q = p->next[idx];
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
            for (auto e : u->next) {
            	Stmt i = e.first;
            	q = e.second;
            	Q.push(q);
            	p = u->fail;
            	to_decidable(i, p);
            	map<Stmt, Node*>::iterator it;
            	while (p != NULL && (it = p->next.find(i)) == p->next.end()) {
            		p = p->fail;
            		to_decidable(i, p);
            	}
            	if (p == NULL || it == p->next.end()) {
            		q->fail = root;
            	} else { 
            		q->fail = it->second;
            	}
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
		return u->next.count(x) != 0;
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
					auto u_next = u->next.find(idx);
					if (u_next != u->next.end()) {
						has = 1;
						v = u_next->second;
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

inline static int tokenizer(char s[], char *tok[]) {
	int m = 0;
	for (int i = 0; s[i]; i++) {
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
	static const int MAXNODE = 1048576;
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

int read_note(int m, Stmt stmts[]) {
	static char s[65536];
	static char *tok[1024];
	int pos = 0;
	trie.init();
	for (int i = 0; i < m; i++) {
		fgets(s, 1024, stdin);
		int n = tokenizer(s, tok);
		int a, b, c;
		if (n == 3) {
			a = encode(tok[0], pos);
			b = encode(tok[2], pos);
			c = 0, pos++;
		} else {
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
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d", &n);

		static Stmt stmts[MAXS];
		static int pos[50005];
		static int ret[50005];
		
		ac.init();
		int tot = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &m); while (getchar() != '\n');
			read_note(m, stmts);
			
			int pid = ac.insert(stmts, m, i);
			tot += pid == i;
			ret[i] = -1;
			pos[i] = pid;
		}		
		ac.build();

		scanf("%d", &m); while (getchar() != '\n');
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
