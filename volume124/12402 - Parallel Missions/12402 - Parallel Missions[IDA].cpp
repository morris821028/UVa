#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;
const int MAXM = 8;
int A[MAXN][MAXM], sA[MAXN][MAXM], An[MAXN];
int Aptr[MAXN], n;
int ida_dep, solved;
int path[MAXN*MAXM];
static inline int log2int(int x) {
	return 31 - __builtin_clz(x);
}
int H() {
	int ret = 0;
	int mask = 0;
	for (int i = 0; i < n; i++) {
		ret = max(ret, An[i] - Aptr[i]);
		for (int j = Aptr[i]; j < An[i]; j++)
			mask |= A[i][j];
	}
	ret = max(ret, (int) __builtin_popcount(mask));
	return ret;
}
const int MAXH = 100007;
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
	VAL& operator[](KEY key) {
		int h = key%MAXH;
		for (int i = head[h]; i; i = hnodes[i].next) {
			if (hnodes[i].k == key)
				return hnodes[i].t;
		}
		++hsize;
		hnodes[hsize].t = 0x3f, hnodes[hsize].k = key;
		hnodes[hsize].next = head[h], head[h] = hsize;
		return hnodes[hsize].t;
	}
};
HASH<int32_t, int8_t> R;

int IDA(int dep, int hval, int sign) {
	if (dep + hval > ida_dep)
		return dep + hval;
	if (hval == 0) {
		solved = dep;
		for (int i = 0; i <= dep; i++)
			printf("%d%c", log2int(path[i]), " \n"[i==dep]);
		return dep;
	}
	
	int8_t &Rstep = R[sign];
	if (Rstep <= dep)
		return 0x3f3f3f3f;
	Rstep = dep;
	int ret = 0x3f3f3f3f, has = 0;
	for (int i = 0; i < n; i++) {
		int idx = (sign>>(i*3))&7;
		has |= A[i][idx];
	}
	
	while (has) {
		int pick = has&(-has);
		int next_sign = 0, hh = 0, h2 = 0;
		for (int i = 0; i < n; i++) {
			int idx = (sign>>(i*3))&7;
			if (A[i][idx] == pick)
				idx++;
			h2 |= sA[i][idx];
			next_sign |= idx<<(i*3);
			hh = max(hh, An[i]-idx);
		}
		hh = max(hh, (int) __builtin_popcount(h2));
		
		path[dep+1] = pick;
		int back = IDA(dep+1, hh, next_sign);
		if (solved >= 0)	return solved;
		has -= has&(-has);
		ret = min(ret, back);
	}
	return ret;
}
int main() {
	int st;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &An[i]);
			for (int j = 0; j < An[i]; j++)
				scanf("%d", &A[i][j]), A[i][j] = 1<<A[i][j];
			sA[i][An[i]] = 0, A[i][An[i]] = 0;
			for (int j = An[i]-1; j >= 0; j--)
				sA[i][j] = sA[i][j+1] | A[i][j];
			Aptr[i] = 0;
		}
		
		scanf("%d", &st);
		
		st = 1<<st; 
		int32_t sign = 0;
		for (int i = 0; i < n; i++) {
			while (Aptr[i] < An[i] && A[i][Aptr[i]] == st)
				Aptr[i]++;
			sign |= (int32_t) Aptr[i]<<(i*3);
		}
		path[0] = st;
		solved = -1;
        ida_dep = H();
        while (solved < 0 && ida_dep <= 20) {
            ida_dep = IDA(0, H(), sign);
            R.clear();
        }
        assert(solved >= 0);
	}
	return 0;
}
/*
3
5 2 3 5 1 2
5 5 2 3 4 5
5 4 2 4 1 4
4

1
1 4
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
