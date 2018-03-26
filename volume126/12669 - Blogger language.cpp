#include <bits/stdc++.h> 
using namespace std;
static const int MAXN = 131072;
static char P[8], T[MAXN];
static int8_t A[MAXN];
static int n, m;
int mismatch(int pos) {
	int ret = 0;
	static const int8_t MASK = ((1<<8)-1)^32;
	for (int i = 0; P[i]; i++) {
		if ((P[i]&MASK) != (T[pos+i]&MASK))
			return -1;
		ret += P[i] != T[pos+i];
	}
	return ret;
}

template<typename T>
T s_min(T a, T b) {
	if (a == -1) return b; 
	if (b == -1) return a; 
	return a < b ? a : b; 
}
template<typename T>
T s_max(T a, T b) {
	return a > b ? a : b; 
}
struct Node {
	int8_t mx, mn, inv;
	Node(int v=0) {
		mx = mn = v, inv = 0;
	}
	void inverse() {
		inv = !inv;
		if (mx != -1)
			mx = m-mx;
		if (mn != -1)
			mn = m-mn;
		swap(mx, mn);
	}
};
static Node tree[MAXN<<2];
static int q_ret, q_l, q_r;
inline void pushdown(int k) {
	if (tree[k].inv) {
		tree[k].inv = 0;
		tree[k<<1].inverse(), tree[k<<1|1].inverse();
	}
}
inline void pushup(int k) {
	tree[k].mx = s_max(tree[k<<1].mx, tree[k<<1|1].mx);
	tree[k].mn = s_min(tree[k<<1].mn, tree[k<<1|1].mn);
}
void build(int k, int l, int r) {
	if (l == r) {
		tree[k] = Node(A[l]);
		return ;
	}
	int m = (l+r)/2;
	build(k<<1, l, m);
	build(k<<1|1, m+1, r);
	tree[k].inv = 0;
	pushup(k);
}

void query(int k, int l, int r) {
	if (tree[k].mx <= q_ret)
		return;
	if (q_l <= l && r <= q_r) {
		q_ret = tree[k].mx;
		return;
	}
	pushdown(k);
	int m = (l+r)/2;
	if (q_l <= m)
		query(k<<1, l, m);
	if (q_r > m)
		query(k<<1|1, m+1, r);
}
void flip(int k, int l, int r) {
	if (q_l <= l && r <= q_r) {
		tree[k].inverse();
		return;
	}
	pushdown(k);
	int m = (l+r)/2;
	if (q_l <= m)
		flip(k<<1, l, m);
	if (q_r > m)
		flip(k<<1|1, m+1, r);
	pushup(k);
}
void fetch(int k, int l, int r) {
	if (l == r) {
		if (tree[k].inv) {
			tree[k].inv = 0;
			T[l] = T[l]^32;	// upper->lower, lower->upper
		}
		return;
	}
	pushdown(k);
	int m = (l+r)/2;
	if (q_l <= m)
		fetch(k<<1, l, m);
	if (q_r > m)
		fetch(k<<1|1, m+1, r);
	pushup(k);
}
void modify(int k, int l, int r) {
	if (l == r) {
		tree[k].mx = tree[k].mn = A[l];
		return;
	}
	pushdown(k);
	int m = (l+r)/2;
	if (q_l <= m)
		modify(k<<1, l, m);
	if (q_r > m)
		modify(k<<1|1, m+1, r);
	pushup(k);
}
int main() {
	int Q;
	while (scanf("%d %s", &Q, P) == 2) {
		scanf("%s", T);
		n = strlen(T), m = strlen(P);
		for (int i = 0; i < n; i++)
			A[i] = mismatch(i);
		build(1, 0, n-1);
		for (int i = 0; i < Q; i++) {
			int l, r;
			scanf("%d %d", &l, &r), l--, r--;
			q_l = l, q_r = r-m+1, q_ret = -1;
			if (q_l <= q_r)
				query(1, 0, n-1);
			printf("%d\n", q_ret);
			// flip substring
			q_l = l, q_r = r;
			if (q_l <= q_r)
				flip(1, 0, n-1);
			// update left, right boundary
			q_l = max(l-m+1, 0), q_r = min(min(l+m, r-m+1), n)-1;
			if (q_l <= q_r)
				fetch(1, 0, n-1);
			q_l = max(r-m+1, 0), q_r = min(r+m, n)-1;
			if (q_l <= q_r)
				fetch(1, 0, n-1);
				
			q_l = max(l-m+1, 0), q_r = l-1;
			int ch = 0;
			for (int i = q_l; i < l; i++) {
				if (A[i] >= 0) {
					A[i] = mismatch(i);
					ch = 1;
				}
			}
			if (q_l <= q_r && ch)
				modify(1, 0, n-1);
			ch = 0;
			q_l = max(r-m+1, 0), q_r = r;
			for (int i = q_l; i <= r; i++) {
				if (A[i] >= 0) {
					A[i] = mismatch(i);
					ch = 1;
				}
			}
			if (q_l <= q_r && ch)
				modify(1, 0, n-1);
		}
	}
	return 0;
}
/*
3 gR
PrOgRAMmINgiSgrEAt
1 7
4 18
6 14
9 abCAb
aBcAbCAbaBCAb
1 13
1 13
4 8
5 11
3 11
4 10
1 13
8 8
1 13
*/
