#include <stdio.h> 
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
struct E1 {
	int C, D;
	E1(int a=0, int b=0):
		C(a), D(b) {}
	bool operator<(const E &a) const {
		if(D - C != a.D - a.C)
			return D - C < a.D - a.C;
	 	return C > a.C;
	}
};
struct E2 {
	int C, D;
	E2(int a=0, int b=0):
		C(a), D(b) {}
	bool operator<(const E &a) const {
	 	return C > a.C;
	}
};
int main() {
	int testcase;
	int N, K, D, C;
	int i, j, k;
	long long M;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %lld", &N, &K, &M);
		vector< pair<int, int> > items;
		for(i = 0; i < N; i++) { // D[i] <= C[i];
			scanf("%d %d", &C, &D);
			items.push_back(make_pair(D, C));
		}
		sort(items.begin(), items.end());
		long long cost = 0;
		set<E1> chK;
		set<E1> nchK;
		set<E2> nchK2;
		for(i = 0; i < N; i++) {
			if(chK.size() <= K) {
				if(cost + items[i].first <= M) {
					chK.insert(E1(items[i].second, items[i].first));
					cost += items[i].first;
				}
			} else {
				cost += items[i].second;
				nchK.insert(E2(items[i].first, item[i].second));
				while(true) {
					set<E1>::iterator it = chK.begin();
					set<E1>::iterator jt = nchK.begin();
					E1 a, b;
					E2 c;
					if(it->C - it->D < jt->C - jt->D) {
						cost -= (jt->C- jt->D) - (it->C- it->D);
						a = *it, b = *jt;
						chK.remove(a), nchK.remove(b);
						chK.insert(b), nchK.insert(a);
					} else {
						break;
					}
				}
				while(cost > M) {
					set<E2>::iterator it = nchK2
				}
			}
		}
		printf("%d\n", chK.size() + nchK.size());
	}
	return 0;
}
/*
2
3 0 6
1 1
2 2
3 3
4 1 7
3 2
2 2
8 1
4 3
*/
