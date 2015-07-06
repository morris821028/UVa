#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
const int MAXS = 35;
class ModeQuery {
public:
	struct Kit {
		unsigned short cnt[MAXN], freq[MAXN];
		int mode_idx;
		Kit() {
			init();
		}
		void init() {
			mode_idx = 0;
		}
		void add(int x, int val) {
			freq[cnt[x]]--;
			cnt[x] += val;
			freq[cnt[x]]++;
			if (cnt[x] > mode_idx)
				mode_idx = cnt[x];
		}
		void resume(int x, int val) {
			freq[cnt[x]]--;
			cnt[x] -= val;
			freq[cnt[x]]++;
		} 
	} f[MAXS * MAXS/2], kit;
	int fr[MAXS][MAXS];
	int A[MAXN], N, PILE, belong[MAXN];
	vector< pair<int, int> > V;
	void heavy() {
		int ff = 0;
		for (int i = 0; i < V.size(); i++)
			for (int j = i; j < V.size(); j++)
				fr[i][j] = ff++;
		for (int i = 0; i < V.size(); i++)
			for (int j = 0; j < i; j++)
				fr[i][j] = ff;
		for (int i = 0; i < V.size(); i++) {
			f[fr[i][i]].init();
			for (int j = V[i].first; j <= V[i].second; j++)
				f[fr[i][i]].add(A[j], 1);
		}
		for (int i = 0; i < V.size(); i++) {
			for (int j = i+1; j < V.size(); j++) {
				f[fr[i][j]] = f[fr[i][j-1]];
				for (int k = V[j].first; k <= V[j].second; k++)
					f[fr[i][j]].add(A[k], 1);
			}
		}
	}
	void make(int n) {
		N = n;
		PILE = (int) pow(n, 0.70) + 1;
				
		V.clear();
		for (int l = 0, r; l < N; l = r+1) {
			r = min(l + PILE - 1, N-1);
			V.push_back(make_pair(l, r));
		}
		for (int i = N-1; i >= 0; i--)
			belong[i] = i / PILE;
		heavy();
	}
	void query(int l, int r, int &a, int &b) {
		int bl = belong[l], br = belong[r];
		if (bl == br || r - l <= PILE + 10) {
			kit.init();
			for (int i = l; i <= r; i++)
				kit.add(A[i], 1);
			a = kit.freq[kit.mode_idx], b = kit.mode_idx;
			for (int i = l; i <= r; i++)
				kit.resume(A[i], 1);
			return ;
		}
		if (l >= 0 && belong[l-1] == bl)	
			bl++;
		if (r < N && belong[r+1] == br)
			br--;
		Kit &tmp = f[fr[bl][br]];
		int tmp_mode_idx = tmp.mode_idx;
		for (int i = bl*PILE - 1; i >= l; i--)
			tmp.add(A[i], 1);
		for (int i = (br+1)*PILE; i <= r; i++)
			tmp.add(A[i], 1);
		a = tmp.freq[tmp.mode_idx], b = tmp.mode_idx;
		for (int i = bl*PILE - 1; i >= l; i--)
			tmp.resume(A[i], 1);
		for (int i = (br+1)*PILE; i <= r; i++)
			tmp.resume(A[i], 1);
		tmp.mode_idx = tmp_mode_idx;
	}
} dream;
int main() {
	int n, m, l, r, a, b;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &dream.A[i]);
		dream.make(n);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &l, &r);
			l--, r--;
			dream.query(l, r, a, b);
			printf("%d %d\n", b, a);
		}
	}
	return 0;
}
/*
10 10
2 3 1 1 1 2 1 2 1 1
5 8
1 10
6 9
5 9
1 5
3 10
1 9
1 1
6 9
2 3
*/

