#include <bits/stdc++.h> 
using namespace std;

struct E {
	int id, s;
	E(int a = 0, int b = 0):
		id(a), s(b) {}
	bool operator<(const E &x) const {
		if (s != x.s)	return s > x.s;
		return id < x.id;
	}
};
int main() {
	int N, R, Q;
	int s, w[262144];
	while (scanf("%d %d %d", &N, &R, &Q) == 3) {
		N <<= 1;
		vector<E> A, B, C;
		for (int i = 1; i <= N; i++)
			scanf("%d", &s), A.push_back(E(i, s));
		for (int i = 1; i <= N; i++)
			scanf("%d", &w[i]);
		sort(A.begin(), A.end());
		for (int i = 0; i < R; i++) {
			B.clear(), C.clear();
			for (int j = 0; j < N; j += 2) {
				if (w[A[j].id] > w[A[j+1].id])
					swap(A[j], A[j+1]);
				A[j+1].s++;
				B.push_back(A[j]);
				C.push_back(A[j+1]);
			}
			A.clear();
			merge(B.begin(), B.end(), C.begin(), C.end(), A.begin());
		}
		printf("%d\n", A[Q-1].id);
	}
	return 0;
}
