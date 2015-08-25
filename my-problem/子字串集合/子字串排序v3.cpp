#include <bits/stdc++.h> 
using namespace std;
class DATrie {
public:
	static const int MAXN = 500000;
	static const int MAXC = 27;
	struct Node {
		int check, base, fail, val;
	} A[MAXN + MAXC];
	int node_size, mem_size, emp_size;
	//
	int son_pos[MAXC], find_pos;
	inline int toIndex(char c) {
		return c - 'A' + 1;
    }
    inline int toChar(char c) {
		return c + 'A' - 1;
    }
    inline bool isEMPTY(int u) {
    	return u < MAXN && A[u].check < 0 && A[u].base < 0;
    }
	void init() {
		for (int i = 1; i < MAXN; i++)
			A[i].check = -(i+1), A[i].base = -(i-1);
		for (int i = MAXN; i < MAXN + MAXC; i++)
			A[i].check = INT_MAX;
		A[MAXN-1].check = -1, A[1].base = -(MAXN-1);
		A[0].check = -1, A[0].base = 0;
		node_size = mem_size = emp_size = 0, find_pos = 1;
	}
	inline void rm_node(int x) {
		if (find_pos == x)	find_pos = abs(A[x].check);
		A[-A[x].base].check = A[x].check;
		A[-A[x].check].base = A[x].base;
		node_size++;
		mem_size = max(mem_size, x);
	}
	inline void ad_node(int x) {
		A[x].check = MAXN, A[x].base = MAXN;
		emp_size++;
	}
	bool insert(const char *s) {
		int st = 0, to, c;
		int flag = 0;
		for (int i = 0; s[i]; i++) {
			c = toIndex(s[i]);
			to = abs(A[st].base) + c;	
			if (st == abs(A[to].check)) {
				st = to;
			} else if (isEMPTY(to)) {
				rm_node(to); 
				A[to].check = st, A[to].base = to;
				st = to;
			} else {
				int son_sz = 0;
				int pos = find_empty(st, c, son_sz);
				relocate(st, pos, son_sz-1);
				i--; 
			}
		}
		A[st].base = -abs(A[st].base);
		return 1;
	}
	int find(const char *s) {
		int st = 0, to, c;
		for (int i = 0; s[i]; i++) {
			c = toIndex(s[i]);
			to = abs(A[st].base) + c;
			if (st == abs(A[to].check))
				st = to;
			else
				return 0;
		}
		return A[st].base < 0;
	}
	int find_empty(int st, int c, int &sz) {
		sz = 0;
		int bs = abs(A[st].base);
		for (int i = 1, j = bs+1; i < MAXC; i++, j++) {
			if (abs(A[j].check) == st)
				son_pos[sz++] = i;
		}
		son_pos[sz++] = c;
		int mn_pos = min(son_pos[0], c) - 1;
		for (; find_pos && (find_pos < bs || find_pos < mn_pos); find_pos = abs(A[find_pos].check));
		for (; find_pos; find_pos = abs(A[find_pos].check)) {
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
			int a = abs(A[st].base) + son_pos[i];	// old
			int b = to + son_pos[i];			// new
			rm_node(b);
			A[b].check = st, A[b].base = A[a].base;
			int vs = abs(A[a].base);
			for (int j = 1, k = vs+1; j < MAXC; j++, k++) {
				if (abs(A[k].check) == a)
					A[k].check = b;
			}
			ad_node(a);
		}
		A[st].base = (A[st].base < 0 ? -1 : 1) * to;
	}
	void dfs(int u, int idx, char path[]) {
		for (int i = 1; i < MAXC; i++) {
			int to = abs(A[u].base) + i;
			if (u == abs(A[to].check)) {
				path[idx] = toChar(i);
				path[idx+1] = '\0';
				puts(path);
				dfs(to, idx+1, path);
			}
		}
	}
	void print() {
		char s[1024];
		dfs(0, 0, s);
	}
} tree;
char s[1024];
int main() {
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		tree.init();
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				char c = s[j+1];
				s[j+1] = '\0';
				tree.insert(s+i);
				s[j+1] = c;
			}
		}
		tree.print();
	}
	return 0;
}

