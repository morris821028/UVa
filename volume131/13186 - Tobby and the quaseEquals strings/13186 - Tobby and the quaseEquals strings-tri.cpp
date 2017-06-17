#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
 
#define MAXNODE 1048576
#define MAXCHAR 27
#define MAXN 131072
#define MAXS 1048576
typedef struct Node {
    int check, base;
    int cnt;
} Node;
Node A[MAXNODE + MAXCHAR];
int node_size, mem_size, emp_size;
int son_pos[MAXCHAR], find_pos;
#define toIndex(c) (c - 'a' + 1)
#define toChar(c) (c + 'a' - 1)
#define max(x, y) (x) > (y) ? (x) : (y)
#define min(x, y) (x) < (y) ? (x) : (y)
#define HASNEXT(u, c)    (u == abs(A[abs(A[u].base) + (c)].check))
#define NEXT(u, c)    (abs(A[u].base) + (c))
#define isEMPTY(u)  (u < MAXNODE && A[u].check < 0 && A[u].base < 0)
void init() {
    for (int i = 1; i < MAXNODE; i++)
        A[i].check = -(i+1), A[i].base = -(i-1), A[i].cnt = 0;
    for (int i = MAXNODE; i < MAXNODE + MAXCHAR; i++)
        A[i].check = INT_MAX;
    A[MAXNODE-1].check = -1, A[1].base = -(MAXNODE-1);
    A[0].check = -1, A[0].base = 0;
    node_size = mem_size = emp_size = 0, find_pos = 1;
}
extern inline void rm_node(int x) {
    if (find_pos == x)    find_pos = abs(A[x].check);
    A[-A[x].base].check = A[x].check;
    A[-A[x].check].base = A[x].base;
    node_size++;
    mem_size = max(mem_size, x);
}
extern inline void ad_node(int x) {
    A[x].check = MAXNODE, A[x].base = MAXNODE;
    emp_size++;
}
int find_empty(int st, int c, int *sz) {
    *sz = 0;
    int bs = abs(A[st].base);
    for (int i = 1, j = bs+1; i < MAXCHAR; i++, j++) {
        if (abs(A[j].check) == st)
            son_pos[(*sz)++] = i;
    }
    son_pos[(*sz)++] = c;
    int mn_pos = min(son_pos[0], c) - 1;
    for (; find_pos && (find_pos < bs || find_pos < mn_pos); find_pos = abs(A[find_pos].check));
    for (; find_pos; find_pos = abs(A[find_pos].check)) {
        int ok = 1;
        for (int i = 0; i < *sz && ok; i++)
            ok &= isEMPTY(find_pos + son_pos[i] - mn_pos);
        if (ok)
            return find_pos - mn_pos;
    }
    printf("Memory Leak -- %d\n", find_pos);
    exit(0);
    return -1;
}
void relocate(int st, int to, int sz) {    // move ::st -> ::to
    for (int i = sz-1; i >= 0; i--) {
        int a = abs(A[st].base) + son_pos[i];    // old
        int b = to + son_pos[i];            // new
        rm_node(b);
        A[b] = A[a];
        int vs = abs(A[a].base);
        for (int j = 1, k = vs+1; j < MAXCHAR; j++, k++) {
            if (abs(A[k].check) == a)
                A[k].check = b;
        }
        ad_node(a);
    }
    A[st].base = (A[st].base < 0 ? -1 : 1) * to;
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
            int pos = find_empty(st, c, &son_sz);
            relocate(st, pos, son_sz-1);
            i--;
        }
    }
    A[st].base = -abs(A[st].base), A[st].cnt++;
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

// fuzzy find
static int N, Q, L;
static int ret = 0;
void fuzzy_find(int u, char *s, int fuzzy_edit, int dep) {
	if (dep == L) {
		if (fuzzy_edit == 1)
			ret += A[u].cnt;
		else
			ret += A[u].cnt * L;
		return ;
	}
	if (fuzzy_edit == 1) {
		if (HASNEXT(u, toIndex(*s)))
			fuzzy_find(NEXT(u, toIndex(*s)), s+1, fuzzy_edit, dep+1);
	} else {
		for (int i = 0; i < MAXCHAR; i++) {
			if (!HASNEXT(u, i))
				continue;
			fuzzy_find(NEXT(u, i), s+1, fuzzy_edit+(toIndex(*s) != i), dep+1);
		}
	}
}
int main() {
	static char s[131072];
    while (scanf("%d %d %d", &N, &Q, &L) == 3) {
    	init();
    	for (int i = 0; i < N; i++) {
    		scanf("%s", s);
    		insert(s);
		}
		
		for (int i = 0; i < Q; i++) {
			scanf("%s", s);
			ret = 0;
			fuzzy_find(0, s, 0, 0);
			printf("%d\n", ret);
		}
	}
    return 0;
}
