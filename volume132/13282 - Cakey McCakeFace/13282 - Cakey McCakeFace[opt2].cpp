#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 2048;
struct Node {
	int val, second;
	Node *next;
	Node(Node *next=NULL, int val=0, int j=0):
		next(next), val(val), second(j) {}
};
Node C[MAXN];
int A[MAXN], B[MAXN];
static inline int F(int val, int y) { return B[y]-val; }
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < m; i++)
			scanf("%d", &B[i]);
		map<int, Node*> S;
		for (int i = 0, st = 0; i < n; i++) {
			while (st < m && B[st] <= A[i])
				st++;
			if (st < m) {
				C[i] = Node(NULL, A[i], st);
				int v = F(A[i], st);
				Node *e = &C[i];
				Node* &p = S[v];
				e->next = p, p = e;
			}
		}

		int mx = 0, ret = 0;
		for (auto it = S.begin(); it != S.end(); ) {
			int cnt = 0;
			for (Node *jt = it->second; jt != NULL; ) {
				cnt++;
				Node *u = jt;
				if (u->second+1 < m) {
					u->second++;
					int v = F(u->val, u->second);
					Node* &p = S[v];
					jt = u->next;
					u->next = p, p = u;
				} else {
					jt = jt->next;
				}
			}
			if (cnt > mx)
				mx = cnt, ret = it->first;
			it = S.erase(it);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
5
5
0  10  12  20  30
1  5  17  27  50
*/
