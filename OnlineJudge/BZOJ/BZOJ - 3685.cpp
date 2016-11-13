#include <bits/stdc++.h>
using namespace std;
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
/**
 * Van Emde Boas tree
 */
static inline char log2int(int x) {
	return __builtin_clz((int) 1) - __builtin_clz(x); 
}
static inline void divHL_bit(int u, int x, int &H, int &L) {
	int t = log2int(u)>>1;
	H = x >> t;
	L = x & ((1<<t)-1);
}
static inline int index_bit(int u, int H, int L) {
	int t = log2int(u)>>1;
	return (H<<t) |  L;
}
// auxiliary structure
char *mem_pool = (char *) malloc(64<<20);
struct Node {
	int mx, mn, u;
	Node *summary, **cluster;
	static Node* newNode(int logN) {
		Node *ret = (Node *) mem_pool;
		mem_pool = mem_pool + sizeof(Node);
		ret->build(logN);
		return ret;
	}
	static Node** newSons(int n) {
		Node **ret = (Node **) mem_pool;
		mem_pool = mem_pool + (n * sizeof(Node*));
		return ret;
	}
	Node(int logN) {build(logN);}
	void build(int logN) {
		mx = mn = -1;
		if (logN <= 1) {
			u = 2;
			summary = NULL, cluster = NULL;
			return ;
		}
		u = 1<<logN;

		int auxN = (logN+1)>>1;
		summary = newNode(auxN);
		cluster = newSons(1<<auxN);
		for (int i = 0; i < (1<<auxN); i++)
			cluster[i] = newNode(logN>>1);
	}
};
struct vEB {    
	Node *root;
	void build(int n) {
		int logN = log2int(n);
		if ((n&(-n)) != n)
			logN++;
		root = Node::newNode(logN);
	}
	int min() {return _min(root);}
	int max() {return _max(root);}
	void insert(int x) {_insert(root, x);}
	void erase(int x) {_erase(root, x);}
	int next(int x) {return _next(root, x);}
	int prev(int x) {return _prev(root, x);}
	int count(int x) {return _count(root, x);}
	// method
	static inline int _min(Node *u) {return u->mn;}
	static inline int _max(Node *u) {return u->mx;}
	static void _insert(Node *u, int x) {
		if (u->mn == x || u->mx == x)
			return ;
		if (u->mn == -1) {
			u->mn = u->mx = x;
			return ;
		}
		// lazzy evaluation
		if (x < u->mn)
			swap(x, u->mn);
		if (x > u->mx)
			u->mx = x;

		if (likely(u->u > 2)) {
			int H, L;
			divHL_bit(u->u, x, H, L);
			if (_min(u->cluster[H]) == -1) {
				_insert(u->summary, H);
				u->cluster[H]->mn = u->cluster[H]->mx = L;
			} else {
				_insert(u->cluster[H], L);
			}
		}
	}
	static void _erase(Node *u, int x) {
		if (u->mn == u->mx) {
			u->mn = u->mx = -1;
			return ;
		}
		if (unlikely(u->u == 2)) {
			u->mn = u->mx = !x;
		} else {
			if (x == u->mn) {
				int first = _min(u->summary);
				x = index_bit(u->u, first, _min(u->cluster[first]));
				u->mn = x;
			}
			int H, L;
			divHL_bit(u->u, x, H, L);
			_erase(u->cluster[H], L);
			if (_min(u->cluster[H]) == -1) {
				_erase(u->summary, H);
				if (x == u->mx) {
					int last = _max(u->summary);
					if (last == -1)
						u->mx = u->mn;
					else
						u->mx = index_bit(u->u, last, _max(u->cluster[last]));
				}
			} else if (x == u->mx) {
				u->mx = index_bit(u->u, H, _max(u->cluster[H]));
			}
		}
	}
	static int _prev(Node *u, int x) {
		if (unlikely(u->u == 2)) {
			if (x == 1 && u->mn == 0)
				return 0;
			return -1;
		}

		if (u->mx != -1 && x > u->mx)
			return u->mx;

		int H, L, Hmn;
		divHL_bit(u->u, x, H, L);
		Hmn = _min(u->cluster[H]);
		if (Hmn != -1 && L > Hmn) {
			return index_bit(u->u, H, _prev(u->cluster[H], L));
		} else {
			int prev_cluster = _prev(u->summary, H);
			if (prev_cluster == -1) {
				if (u->mn != -1 && x > u->mn)
					return u->mn;
				return -1;
			} else {
				return index_bit(u->u, prev_cluster, _max(u->cluster[prev_cluster]));
			}
		}
	}
	static int _next(Node *u, int x) {
		if (u->u == 2) {
			if (x == 0 && u->mx == 1)
				return 1;
			return -1;
		}

		if (u->mn != -1 && x < u->mn)
			return u->mn;

		int H, L, Hmx;
		divHL_bit(u->u, x, H, L);
		Hmx = _max(u->cluster[H]);
		if (Hmx != -1 && L < Hmx) {
			return index_bit(u->u, H, _next(u->cluster[H], L));
		} else {
			int next_cluster = _next(u->summary, H);
			if (next_cluster == -1) {
				if (u->mx != -1 && x < u->mx)
					return u->mx;
				return -1;
			} else {
				return index_bit(u->u, next_cluster, _min(u->cluster[next_cluster]));
			}
		}
		return 0;
	}
	static int _count(Node *u, int x) {
		if (x == u->mn || x == u->mx)
			return 1;
		if (u->u == 2)
			return 0;
		int H, L;
		divHL_bit(u->u, x, H, L);
		return _count(u->cluster[H], L);
	}
};

namespace {
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
			void printInt(int x, char padding) {
				if (x < 0) {
					*p = '-', p++;
					if (p == end)
						*p = '\0', printf("%s", buf), p = buf;
					*p = '1', p++;
					if (p == end)
						*p = '\0', printf("%s", buf), p = buf;
					*p = padding, p++;
					if (p == end)
						*p = '\0', printf("%s", buf), p = buf;
					return ;
				}
				static char stk[16];
				int idx = 0;
				stk[idx++] = padding;
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
			static inline void online_printInt(int x) {
				static char ch[16];
				static int idx;
				idx = 0;
				if (x == 0) ch[++idx] = 0;
				while (x > 0) ch[++idx] = x % 10, x /= 10;
				while (idx) 
					putchar(ch[idx--]+48);
			}
			~Print() {
				*p = '\0';
				printf("%s", buf);
			}
	} bprint;
}
vEB tree;
int main() {
	int n, m, cmd, x;
	ReadInt(&n), ReadInt(&m);
	tree.build(n);
	while (m--) {
		ReadInt(&cmd);
		if (cmd == 1) {
			ReadInt(&x);
			if (!tree.count(x))
				tree.insert(x);
		} else if (cmd == 2) {
			ReadInt(&x);
			if (tree.count(x))
				tree.erase(x);
		} else if (cmd == 3) {
			bprint.printInt(tree.min(), '\n');
		} else if (cmd == 4) {
			bprint.printInt(tree.max(), '\n');
		} else if (cmd == 5) {
			ReadInt(&x);
			bprint.printInt(tree.prev(x), '\n');
		} else if (cmd == 6) {
			ReadInt(&x);
			bprint.printInt(tree.next(x), '\n');
		} else if (cmd == 7) {
			ReadInt(&x);
			bprint.printInt(tree.count(x) ? 1 : -1, '\n');
		}
	}
	return 0;
}
