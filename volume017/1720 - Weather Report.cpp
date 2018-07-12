#include <bits/stdc++.h> 
using namespace std;

struct Node {
	double p;
	int64_t n;
	Node() {}
	Node(double p, int64_t n): p(p), n(n) {}
	bool operator<(const Node &x) {
		return p > x.p;
	}
};

int32_t C[32][32] = {};

void init() {
	C[0][0] = 1;
	for (int i = 1; i < 32; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
}

int main() {
	init();
	
	int n;
	double p[4];
	while (scanf("%d", &n) == 1) {
		scanf("%lf %lf %lf %lf", &p[0], &p[1], &p[2], &p[3]);
		
		static Node pQ[4096];
		int qn = 0;
		double mpow[4][32];
		for (int k = 0; k < 4; k++) {
			mpow[k][0] = 1;
			for (int i = 1; i <= n; i++)
				mpow[k][i] = mpow[k][i-1]*p[k];
		}
		for (int i = 0; i <= n; i++)  {
			for (int j = 0; i+j <= n; j++) {
				for (int k = 0; i+j+k <= n; k++) {
					int l = n-i-j-k;
					double q = mpow[0][i] * mpow[1][j] * mpow[2][k] * mpow[3][l];
					int64_t x = (int64_t) C[n][i] * C[n-i][j] * C[n-i-j][k];
					pQ[qn++] = Node(q, x);
				}
			}
		}
				
		make_heap(pQ, pQ+qn);
		double ret = 0;
		Node last(0, 0);
		while (qn) {
			Node it = pQ[0]; pop_heap(pQ, pQ+qn); qn--;
			if (qn == 0 && it.n + last.n == 1)
				break;
			if (last.n == 1) {
				pQ[qn++] = Node(it.p + last.p, 1); push_heap(pQ, pQ+qn);
				ret += it.p + last.p;
				it.n--, last.n = 0;
			}
			if (it.n > 0) {
				if (it.n >= 2) {
					pQ[qn++] = Node(it.p + it.p, it.n/2); push_heap(pQ, pQ+qn);
					ret += (it.p + it.p) * (it.n/2);
				}
				if (it.n&1)
					last.n = 1, last.p = it.p;
			}
		}
		printf("%.6lf\n", ret);
	}
	return 0;
}
/*
2
0.9 0.049999 0.05 0.000001
20
0.25 0.25 0.25 0.25
*/
