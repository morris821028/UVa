#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;
const int MAXM = 8;
const int MAXH = 1000007;
int A[MAXN][MAXM], An[MAXN];
int Aptr[MAXN], n;
static inline int log2int(int x) {
	return 31 - __builtin_clz(x);
}
int H() {
	int ret = 0;
	for (int i = 0; i < n; i++)
		ret = max(ret, An[i] - Aptr[i]);
	return ret;
}
int32_t encode_Aptr() {
	int32_t sign = 0;
	for (int i = 0; i < n; i++)
		sign |= Aptr[i]<<(i*3);
	return sign;
}
template<typename KEY, typename VAL>
class HASH {
public:
	struct HN {
		KEY k;
		VAL t; 
		int32_t next;
	} hnodes[MAXH*10];
	int head[MAXH], hsize;
	void clear() {
		hsize = 0;
		memset(head, 0, sizeof(head));
	}
	void insert(KEY key, VAL val) {
		int h = key%MAXH;
		++hsize;
		assert(hsize < MAXH*10);
		hnodes[hsize].t = val, hnodes[hsize].k = key;
		hnodes[hsize].next = head[h], head[h] = hsize;
	}
	int count(KEY key) {
		int h = key%MAXH;
		for (int i = head[h]; i; i = hnodes[i].next) {
			if (hnodes[i].k == key)
				return 1;
		}
		return 0;
	}
	VAL get(KEY key) {
		int h = key%MAXH;
		for (int i = head[h]; i; i = hnodes[i].next) {
			if (hnodes[i].k == key)
				return hnodes[i].t;
		}
	}
};
HASH< int32_t, pair<int32_t, int32_t> > R;
void AStar(int st) {
	struct AE {
		int32_t x, dep, h;
		AE(int32_t x, int32_t dep, int32_t h):
			x(x), dep(dep), h(h) {}
		bool operator<(const AE &other) const {
			if (dep+h != other.dep+other.h)
				return dep+h > other.dep+other.h;
			if (dep != other.dep)
				return dep > other.dep;
			return x < other.x;
		}
	};
	R.clear();
//	unordered_map< int32_t, pair<int32_t, int32_t> > R;
	priority_queue<AE> P;
	
	for (int i = 0; i < n; i++) {
		while (Aptr[i] < An[i] && A[i][Aptr[i]] == st)
			Aptr[i]++;
	}
	
	AE init(encode_Aptr(), 1, H());
//	P.insert(init);
	P.push(init);
	R.insert(init.x, make_pair(-1, st));
//	 R[init.x] = make_pair(-1, st);
	
	if (init.h == 0) {
		printf("%d\n", log2int(st));
		return ;
	}
	while (!P.empty()) {
//		AE u = *P.begin();
//		P.erase(P.begin());
		AE u = P.top();
		P.pop();
//		printf("%d %d\n", u.x, u.dep);
		int has = 0;
		for (int i = 0; i < n; i++) {
			int idx = (u.x>>(i*3))&7;
			if (idx < An[i])
				has |= A[i][idx];
		}
		while (has) {
			int pick = has&(-has);
			int mark = 0, sign = 0, h = 0;
			for (int i = 0; i < n; i++) {
				int idx = (u.x>>(i*3))&7;
				if (idx < An[i] && A[i][idx] == pick)
					idx++;
				sign |= idx<<(i*3);
				h = max(h, An[i] - idx);
			}
			AE v(sign, u.dep+1, h);
			if (R.count(v.x) == 0) {
//				P.insert(v);
				P.push(v);
//				R[v.x] = make_pair(u.x, pick);
				R.insert(v.x, make_pair(u.x, pick));
			}
			if (v.h == 0) {
				vector<int> path;
				int p = v.x;
				while (p != -1) {
//					auto val = R[p];
					auto val = R.get(p);
					path.push_back(val.second);
					p = val.first;
				}
				for (int i = path.size()-1; i >= 0; i--)	
					printf("%d%c", log2int(path[i]), " \n"[i==0]);
				return ;
			}
			has -= has&(-has);
		}
	}
	
	return ;
}
int main() {
	int st;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &An[i]);
			for (int j = 0; j < An[i]; j++)
				scanf("%d", &A[i][j]), A[i][j] = 1<<A[i][j];
			Aptr[i] = 0;
		}
		
		scanf("%d", &st);
		
		st = 1<<st; 
		AStar(st);
	}
	return 0;
}
/*
3
5 2 3 5 1 2
5 5 2 3 4 5
5 4 2 4 1 4
4

10
1 3
6 9 3 6 10 2 9
3 3 2 7
4 2 9 8 2
6 8 2 6 2 10 6
5 5 1 8 6 5
3 6 5 8
5 10 3 6 10 8
6 5 4 1 6 2 10
4 5 4 9 8
1
*/
