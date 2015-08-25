#include <bits/stdc++.h> 
using namespace std;
char buf[1048576<<2];
class DATrie {
public:
	static const int MAXN = 3000000;
	static const int MAXC = 100;
	int check[MAXN + MAXC], base[MAXN];
	int node_size, mem_size, emp_size, words;
	//
	int son_pos[MAXC], find_pos;
	inline int toIndex(char c) {
		return c - 32;
    }
    inline char toChar(char c) {
    	return c + 32;
    }
    inline bool isEMPTY(int u) {
    	return u < MAXN && check[u] < 0 && base[u] < 0;
    }
	void init() {
		for (int i = 1; i < MAXN; i++)
			check[i] = -(i+1), base[i] = -(i-1);
		check[MAXN-1] = 1, base[1] = -(MAXN-1);
		check[0] = -1, base[0] = 0;
		node_size = mem_size = emp_size = 0, find_pos = 1;
		words = 0;
	}
	inline void rm_node(int x) {
		if (find_pos == x)	find_pos = abs(check[x]);
		assert(-base[x] >= 0);
		check[-base[x]] = check[x];
		assert(-check[x] >= 0);
		base[-check[x]] = base[x];
		node_size++;
		mem_size = max(mem_size, x);
	}
	inline void ad_node(int x) {
		check[x] = MAXN, base[x] = MAXN;
		emp_size++;
	}
	inline int unique_word() {
		return words;
	}
	bool insert(const char *s) {
		int st = 0, to, c;
		int flag = 0;
		for (int i = 0; s[i]; i++) {
			c = toIndex(s[i]);
			to = abs(base[st]) + c;	
			if (to < MAXN && st == check[to]) {
				st = to;
			} else if (isEMPTY(to)) {
				rm_node(to); 
				check[to] = st, base[to] = to;
				st = to;
			} else {
				int son_sz = 0;
				int pos = find_empty(st, c, son_sz);
				relocate(st, pos, son_sz-1);
				i--; 
			}
		}
		if (base[st] > 0)	words++;
		base[st] = -abs(base[st]);
		return 1;
	}
	int find(const char *s) {
		int st = 0, to, c;
		for (int i = 0; s[i]; i++) {
			c = toIndex(s[i]);
			to = abs(base[st]) + c;
			if (st == check[to])
				st = to;
			else
				return 0;
		}
		return base[st] < 0;
	}
	int find_empty(int st, int c, int &sz) {
		sz = 0;
		int bs = abs(base[st]);
		for (int i = 1; i < MAXC; i++) {
			if (check[bs+i] == st)
				son_pos[sz++] = i;
		}
		son_pos[sz++] = c;
		int mn_pos = min(son_pos[0], c) - 1;
		for (; find_pos && (find_pos < bs || find_pos < mn_pos); find_pos = abs(check[find_pos]));
		for (; find_pos; find_pos = abs(check[find_pos])) {
			int ok = 1;
			for (int i = 0; i < sz && ok; i++)
				ok &= isEMPTY(find_pos + son_pos[i] - mn_pos);
			if (ok) {
				return find_pos - mn_pos;
			}
		}
		printf("Memory Leak --");
		exit(0);
		assert(false);
		return -1;
	}
	void relocate(int st, int to, int sz) {	// move ::st -> ::to
		for (int i = sz-1; i >= 0; i--) {
			int a = abs(base[st]) + son_pos[i];	// old
			int b = to + son_pos[i];			// new
			rm_node(b);
			check[b] = st, base[b] = base[a];
			int vs = abs(base[a]);
			for (int j = 1, k = vs+1; j < MAXC; j++, k++) {
				if (check[k] == a)
					check[k] = b;
			}
			ad_node(a);
		}
		base[st] = (base[st] < 0 ? -1 : 1) * to;
	}
	void print() {
		struct Node {
			int ch, dep, st, son, has;
			Node(int a = 0, int b = 0, int c = 0, int d = 0):
				st(a), ch(b), dep(c), son(d) {has = 0;}
		};
		
		char *ptr = buf;
		stack<Node> stk;
		stk.push(Node(0, 0, 0));
		int flag = 0;
		while (!stk.empty()) {
			Node u = stk.top();
			stk.pop();
			if (u.son == 0) {
				if (flag == 1) {
					flag = 0;
					for (int i = 0; i < u.dep; i++) {
						*ptr = ' ', ptr++;
						*ptr = ' ', ptr++;
						*ptr = ' ', ptr++;
					}
				}
				u.son = 1;
				*ptr = '[', ptr++;
				*ptr = toChar(u.ch), ptr++;
				*ptr = ']', ptr++;
			}
			int has = 0;
			for (int i = u.son; i < MAXC; i++, u.son++) {
				int to = abs(base[u.st]) + i;
				if (u.st == check[to]) {
					u.son++, u.has = 1;
					stk.push(u);
					stk.push(Node(to, i, u.dep+1, 0));
					has = 1;
					break;
				}
			}
			if (!has) {
				if (!u.has)	{
					flag = 1;
					*ptr = '\0', ptr++;
					puts(buf);
					ptr = buf;
				}
			}
		} 
	}
} tree;
char s[1048576];
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		getchar();
		tree.init();
		for (int i = 0; i < n; i++) {
			fgets(s, 1048576, stdin);
			s[strlen(s)-1] = '\0';
			tree.insert(s);
		}
		tree.print();
	}
	return 0;
}
/*
*/

