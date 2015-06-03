#include <stdio.h> 
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 65536;

#define HASH_MOD 10007
struct Product {
	int v[5];
	bool operator<(const Product &a) const {
		return sum() < a.sum();
	}
	int sum() const {
		int s = 0;
		for (int i = 0; i < 5; i++)
			s += v[i];
		return s;
	}
	unsigned int hash() {
		unsigned int a = 63689, b = 378551;
		unsigned int value = 0;
		for (int i = 0; i < 5; i++) {
			value = value * a + v[i];
			a *= b;
		}
		return value % HASH_MOD;
	}
	int dist(Product &u) {
		int ret = 0;
		for (int i = 0; i < 5; i++)
			ret += abs(v[i] - u.v[i]);
		return ret;
	}
} D[MAXN], QD;
struct cmp {
	bool operator() (const Product &a, const Product &b) const {
		for (int i = 0; i < 5; i++)
			if (a.v[i] != b.v[i])
				return a.v[i] < b.v[i];
		return false;
	}
};
int N, Q, QK;
vector<int> Comb[5];
set<Product, cmp> S[HASH_MOD];
int isSkyline(Product &u) {
	vector<int> &C = Comb[QK];
	for (int i = 0; i < N && i < 32; i++) {
		int ok = 0;
		for (int j = C.size()-1; j >= 0 && !ok; j--) {
			int ok2 = 1, ok3 = 0;
			for (int k = 0; k < 5 && ok2; k++) {
				if ((C[j]>>k)&1) {
					ok2 &= D[i].v[k] <= u.v[k];
					ok3 |= D[i].v[k] <  u.v[k];
				}
			}
			if (ok2 && ok3)
				ok = 1;
		}
		if (ok || u.dist(D[i]) == 0)
			return 0;
	}
	return 1;
} 
int updateProduct() {
	if (isSkyline(QD))
		return 0;
		
	for (int i = 0; i < HASH_MOD; i++)
		S[i].clear();
	S[QD.hash()].insert(QD);
	queue<Product> 	Q;
	queue<int>		C;
	Product u, v;
	int c;
	Q.push(QD), C.push(0);
	
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		c = C.front(), C.pop();
		for (int i = 0; i < 5; i++) {
			v = u;
			v.v[i]--;
			if (v.v[i] == 0) 
				continue;
			if (S[v.hash()].count(v))
				continue;
			if (isSkyline(v)) {
//				printf("best ");
//				for (int i = 0; i < 5; i++)
//					printf("%d ", v.v[i]);
//				puts("");
				return c+1;
			}
			S[v.hash()].insert(v);
			Q.push(v), C.push(c+1);
		}
	}
	return -1;
}
int main() {
	for (int i = 0; i < (1<<5); i++) {
		int s = 0;
		for (int j = 0; j < 5; j++)
			if ((i>>j)&1)
				s++;
		Comb[s].push_back(i);
	}
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++) {
			int s = 0;
			for (int j = 0; j < 5; j++)
				scanf("%d", &D[i].v[j]);
		}
		sort(D, D+N);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d", &QK);
			for (int j = 0; j < 5; j++)
				scanf("%d", &QD.v[j]);
			printf("%d\n", updateProduct());
		}
	}
	return 0;
}
/*
2
5 20 20 20 20
20 5 20 20 20

2
1
20 20 20 20 20 
1
5 5 20 20 20 

5
8 5 4 9 5 
10 17 1 5 7 
10 17 14 12 1 
8 1 20 1 12 
16 14 3 9 14 
13
1
13 15 7 13 9 
1
8 1 4 1 5


*/
