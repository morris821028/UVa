#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1505;

struct Edge {
	int to, l;
	Edge() {}
	Edge(int to, int l):
		to(to), l(l) {}
} edges[MAXN];

int key_pos[MAXN];
vector<Edge> g[MAXN];

int8_t pass[MAXN];
int8_t ulock[MAXN];
int16_t depth[MAXN];
Edge parent[MAXN];
void dfs(int u, int dep) {
	depth[u] = dep;
	for (auto e : g[u]) {
		if (depth[e.to] != -1)
			continue;
		parent[e.to] = Edge(u, e.l);
		dfs(e.to, dep+1);
	}
}

void root_tree(int u, int n) {
	memset(depth, -1, sizeof(depth));
	dfs(u, 0);
}

Edge* path(int st, int ed, Edge *ret) {
	static Edge tmp[MAXN];
	int n = 0;
	int a = depth[st], b = depth[ed];
	while (a > b) {
	    *ret = Edge(st, parent[st].l), ret++;
		st = parent[st].to, a--;
	}
	while (b > a) {
	    tmp[n++] = parent[ed];
		ed = parent[ed].to, b--;
	}
	while (st != ed) {
		*ret = Edge(st, parent[st].l), ret++;
		st = parent[st].to;
		tmp[n++] = parent[ed];
		ed = parent[ed].to;
	}
	reverse(tmp, tmp+n);
	memcpy(ret, tmp, sizeof(tmp[0])*n), ret += n;
	return ret;
}

static Edge pstk[MAXN*16];
static Edge *pstk_ptr;
int unlock_path(int st, int ed, vector<int> &ret) {
    Edge *begin = pstk_ptr;
	Edge *end = path(st, ed, pstk_ptr);
	pstk_ptr = end;
	
	auto prev = begin;
    auto it = begin;
	for (; it != end; ) {
		if (it->l < 0 || pass[it->l]) {
			it++;
		} else {
			int pos = key_pos[it->l], stop = it->to;
			if (ulock[it->l])	return 1;
			ulock[it->l] = 1;
			if (unlock_path(prev->to, pos, ret)) return 1;
			if (unlock_path(pos, stop, ret))     return 1;
			pass[it->l] = 1;
			ret.push_back(stop);
			prev = ++it;
		}
	}
	
    while (prev != it)
        ret.push_back(prev->to), prev++;
    pstk_ptr = begin;
	return 0;
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
class Print {
public:
    static const int N = 1048576;
    char buf[N], *p, *end;
    Print() {
        p = buf, end = buf + N - 1;
    }
    void putint(int x) {
        static char stk[16];
        int idx = 0;
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
    void putchar(char x) {
    	if (p == end) {
            *p = '\0';
            printf("%s", buf), p = buf;
        }
        *p = x, p++;
	}
	void putstr(char *s) {
		for (; *s; s++) {
			if (p == end) {
	            *p = '\0';
	            printf("%s", buf), p = buf;
	        }
	        *p = *s, p++;
		}
	}
    ~Print() {
        *p = '\0';
        printf("%s", buf);
    }
} bprint;

void solve(int st, int ed, int n) {
	root_tree(ed, n);
	
	memset(pass, 0, sizeof(pass));
	memset(ulock, 0, sizeof(ulock));
	vector<int> path;
	pstk_ptr = pstk;
	int error = unlock_path(st, ed, path);
	if (error) {
//		puts("Impossible");
		bprint.putstr("Impossible\n");
		return ;
	}
	bprint.putint(path.size());
	bprint.putchar(':');
//	printf("%d:", path.size());
	for (auto e : path) {
		bprint.putchar(' ');
		bprint.putint(e);
//		printf(" %d", e);
	}
	bprint.putchar(' ');
	bprint.putint(ed);
	bprint.putchar('\n');
//	printf(" %d\n", ed);
}

int main() {
	int n, m, st, ed;
//	while (scanf("%d %d %d %d", &n, &m, &st, &ed) == 4 && n) {
	while (ReadInt(&n) && n) {
		ReadInt(&m), ReadInt(&st), ReadInt(&ed);
		for (int i = 0; i < n; i++)
			g[i].clear();
			
		for (int i = 0; i < m; i++)
//			scanf("%d", &key_pos[i]);
			ReadInt(&key_pos[i]);
		
		for (int i = 0; i < n-1; i++) {
			int a, b, l;
//			scanf("%d %d %d", &a, &b, &l);
			ReadInt(&a), ReadInt(&b), ReadInt(&l);
			g[a].emplace_back(b, l);
			g[b].emplace_back(a, l);
		}
		
		solve(st, ed, n);
	}
	return 0;
}
/*
1  0  0  0

3  1  0  2
1
0  1  -1
0  2  0

3  2  0  2
1  2
0  1  1
0  2  0

5  3  0  4
2  0  3
0  1  0
0  2  -1
1  3  1
2  4  2

0  0  0  0
*/
