#include <bits/stdc++.h> 
using namespace std;
/*
Fast Walsh¡VHadamard transform 
Fast Fourier Transform and variations of it:
https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
*/
const int MAXV = 100005;
const int MAXE = MAXV<<1;
struct Edge {
    int v, w;
    Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
void Addedge(int x, int y, int w){
    edge[e].v = y, edge[e].w = w, edge[e].next = adj[x];
	adj[x] = &edge[e++];
    edge[e].v = x, edge[e].w = w, edge[e].next = adj[y];
    adj[y] = &edge[e++];
}
const int MAXR = 1<<16;
int64_t ret[MAXR];

template <typename T>
struct FWT {
	void fwt(T io[], int n) {
		for (int d = 1; d < n; d <<= 1) {
			for (int i = 0, m = d<<1; i < n; i += m) {
				for (int j = 0; j < d; j++) {
					T x = io[i+j], y = io[i+j+d];
					io[i+j] = (x+y), io[i+j+d] = (x-y);	// xor
					// io[i+j] = x+y // and
					// io[i+j+d] = x+y // or
				}
			}
		}
	}
	void ufwt(T io[], int n) {
		for (int d = 1; d < n; d <<= 1) {
			for (int i = 0, m = d<<1; i < n; i += m) {
				for (int j = 0; j < d; j++) {
					T x = io[i+j], y = io[i+j+d];
					io[i+j] = (x+y)>>1, io[i+j+d] = (x-y)>>1; // xor
					// io[i+j] = x-y // and
					// io[i+j+d] = y-x // or
				}
			}
		}
	}
	void convolution(T a[], T b[], int n) {
		fwt(a, n);
		fwt(b, n);
		for (int i = 0; i < n; i++)
			a[i] = a[i]*b[i];
		ufwt(a, n);
	}
	void self_convolution(T a[], int n) {
		fwt(a, n);
		for (int i = 0; i < n; i++)
			a[i] = a[i]*a[i];
		ufwt(a, n);
	}
};
FWT<int64_t> fwt;
void dfs(int u, int p, int x) {
	ret[x]++;
	for (Edge *t = adj[u]; t != NULL; t = t->next) {
		if (t->v == p)
			continue;
		dfs(t->v, u, x ^ t->w);
	}
}
int main() {
	int testcase, cases = 0;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		e = 0;
		memset(adj, 0, sizeof(adj[0])*n);
		for (int i = 1; i < n; i++) {
			int x, y, w;
			scanf("%d %d %d", &x, &y, &w);
			x--, y--;
			Addedge(x, y, w);
		}
		memset(ret, 0, sizeof(ret));
		dfs(0, -1, 0);
		fwt.self_convolution(ret, 1<<16);
		printf("Case %d:\n", ++cases);
		printf("%lld\n", (ret[0]-n)>>1);
		for (int i = 1; i < (1<<16); i++)
			printf("%lld\n", ret[i]>>1);
	}
	return 0;
} 
/*
1
4
1 2 5
1 3 2
1 4 1
*/
