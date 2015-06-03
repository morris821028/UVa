#include <stdio.h> 
#include <set>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 40005;
int N, Q, QK;
vector<int> Comb[32];
struct Product {
	int v[5];
	Product() {
		for (int i = 0; i < 5; i++)
			v[i] = 1;
	}
	bool operator<(const Product &a) const {
		return sum() < a.sum();
	}
	int sum() const {
		int s = 0;
		for (int i = 0; i < 5; i++)
			s += v[i];
		return s;
	}
	int dist(Product &u) {
		int ret = 0;
		for (int i = 0; i < 5; i++)
			ret += abs(v[i] - u.v[i]);
		return ret;
	}
	int domain(Product &u, int K) {
		vector<int> &C = Comb[K];	
		for (int j = C.size()-1; j >= 0; j--) {
			int ok2 = 1, ok3 = 0;
			for (int k = 0; k < 5 && ok2; k++) {
				if ((C[j]>>k)&1) {
					ok2 &= v[k] <= u.v[k];
					ok3 |= v[k] <  u.v[k];
				}
			}
			if (ok2 && ok3)
				return 1;
		}
		return 0;
	}
} D[MAXN], QD;
vector<Product> DK[8];

int isSkyline(Product &u) {
	for (int i = 0; i < DK[QK].size() && i < 512; i++) {
		int ok = 0;
		ok = DK[QK][i].domain(u, QK);
		if (ok || u.dist(DK[QK][i]) == 0)
			return 0;
	}
	return 1;
} 
double randDouble() {
	return (rand() % 32767) / 32767.0;
}

#define S_DIV 0.5f
#define S_LEN 512
#define T_CNT 8
#define E_CNT 256
int val[E_CNT];
Product pool[E_CNT];
int updateProduct() {
	if (isSkyline(QD))
		return 0;
	double step[5];
	Product u;
	for (int i = 0; i < 5; i++)
		step[i] = QD.v[i];
	for (int i = 0; i < E_CNT; i++)
		pool[i] = Product(), val[i] = pool[i].dist(QD);
	for (int it = 0; it < 9; it++) {
		for (int i = 0; i < E_CNT; i++) {
			for (int j = 0; j < T_CNT; j++) {
				u = pool[i];
				for (int k = 0; k < 5; k++) {
					u.v[k] = min(u.v[k] + (int) (randDouble() < 0.5 ? 0 : step[k]), QD.v[k]);
				}
				if (isSkyline(u)) {
					int c = u.dist(QD);
					if (c < val[i])
						val[i] = c, pool[i] = u;
				}
			}
		}
		for (int i = 0; i < 5; i++)
			step[i] *= S_DIV; 
	}
	
	int ret = val[0];
	Product best = pool[0];
	for (int i = 0; i < E_CNT; i++) {
		if (val[i] < ret)
			ret = min(ret, val[i]), best = pool[i];
	}
	
//	printf("best ");
//	for (int i = 0; i < 5; i++)
//		printf("%d ", best.v[i]);
//	puts("");
	return ret;
}
int used[MAXN] = {};
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
			for (int j = 0; j < 5; j++)
				scanf("%d", &D[i].v[j]);
		}
		sort(D, D+N);
		
		for (int K = 1; K <= 3; K++) {
			vector<Product> filter;
			for (int i = 0; i < N; i++) {
				if (used[i] == 0) {
					filter.push_back(D[i]);
					for (int j = i+1; j < N; j++)
						if (used[j] == 0 && D[i].domain(D[j], K))
							used[j] = 1;
				}
			}
			for (int i = 0; i < N; i++)
				if (used[i] == 1) 
					filter.push_back(D[i]);
			DK[K] = filter;
			for (int i = 0; i < N; i++)
				used[i] = 0;
		}
		
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
1
20 20 20 20 20
1 
3
20 20 20 20 20

2
5 20 20 20 20
20 5 20 20 20
2
1
20 20 20 20 20 
1
5 5 20 20 20 



*/
