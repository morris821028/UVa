#include <bits/stdc++.h> 
using namespace std;
class DATrie {
public:
	static const int MAXN = 5000000;
	static const int MAXC = 63;
	int check[MAXN + MAXC], base[MAXN], fail[MAXN], val[MAXN];
	int node_size, mem_size, emp_size, words;
	//
	int son_pos[MAXC], find_pos;
	inline int toIndex(char c) {
		if (isdigit(c))	return c - '0' + 1;
		if (isupper(c)) return c - 'A' + 10 + 1;
		if (islower(c))	return c - 'a' + 26 + 10 + 1;
		assert(false);
    }
    inline bool isEMPTY(int u) {
    	return u < MAXN && check[u] < 0 && base[u] < 0;
    }
	void init() {
		for (int i = 1; i < MAXN; i++)
			check[i] = -(i+1), base[i] = -(i-1), fail[i] = -1;
		for (int i = MAXN; i < MAXN + MAXC; i++)
			check[i] = INT_MAX;
		check[MAXN-1] = -1, base[1] = -(MAXN-1);
		check[0] = -1, base[0] = 0;
		node_size = mem_size = emp_size = 0, find_pos = 1;
		words = 0;
	}
	inline void rm_node(int x) {
		if (find_pos == x)	find_pos = abs(check[x]);
		check[-base[x]] = check[x];
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
			if (st == abs(check[to])) {
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
//			printf("insert %d %d %d\n", i, st, c);
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
			if (st == abs(check[to]))
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
			if (ok)
				return find_pos - mn_pos;
		}
		printf("Memory Leak -- %d\n", find_pos);
		exit(0);
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
	void build() { // AC automation
        queue<int> Q;
        int u, p, to, pto;
        Q.push(0), fail[0] = -1;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = 1; i < MAXC; i++) {
            	to = abs(base[u]) + i;
				if (u != abs(check[to]))	
					continue;
                Q.push(to);
                p = fail[u];
                while (p != -1) {
                	pto = abs(base[p]) + i;
                	if (p != abs(check[pto]))
                    	p = fail[p];
                    else
                    	break;
                }
                if (p == -1)
                    fail[to] = 0;
                else
                    fail[to] = abs(base[p]) + i;
                val[to] = val[fail[to]] + (base[to] < 0);
            }
        }
    }
    int query(const char *s) {
    	int st = 0, c, to;
    	int matched = 0;
    	for (int i = 0; s[i]; i++) {
    		c = toIndex(s[i]);
    		do {
    			to = abs(base[st]) + c;
    			if (st != abs(check[to]) && st != 0)
    				st = fail[st];
    			else
    				break;
    		} while (true);
    		to = abs(base[st]) + c;
    		if (st != abs(check[to]))
    			st = 0;
    		else
    			st = to;
    		matched += val[st];
    	}
    	return matched;
    }
} tree;
char s[1048576];
int main() {
	int n, m, cases = 0;
	while (scanf("%d", &n) == 1) {
		printf("Case #%d:\n", ++cases);
		tree.init();
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			tree.insert(s);
		}
		tree.build();
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s", s);
			int t = tree.query(s);
			printf("%d\n", t);
		}
	}
	return 0;
}

