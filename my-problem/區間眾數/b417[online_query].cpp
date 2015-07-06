#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
class ModeQuery {
public:
	int A[MAXN], N, PILE, belong[MAXN];
	vector< vector<int> > V, Vmode;
	vector<int> POS[MAXN];
	int q_dup[MAXN], q_cases;
	void make(int n) {
		N = n, q_cases = 0;
		for (PILE = 1; PILE * PILE < N; PILE <<= 1);
		
		V.clear(), Vmode.clear();
		for (int l = 0, r; l < N; l = r+1) {
			r = min(l + PILE - 1, N-1);
			V.push_back(vector<int>(A+l, A+r+1));
			Vmode.push_back(vector<int>());
		}
		
		for (int i = 0; i < V.size(); i++) {
			sort(V[i].begin(), V[i].end());
			int mx_cnt = 1, cnt = 1;
			for (int j = 1; j <= V[i].size(); j++) {
				if (j == V[i].size() || V[i][j] != V[i][j-1]) {
					if (cnt > mx_cnt)	
						mx_cnt = cnt, Vmode[i].clear();
					if (cnt == mx_cnt)
						Vmode[i].push_back(V[i][j-1]);
					cnt = 1;
				} else {
					cnt++;
				}
			}
		}
		
		for (int i = 1; i <= N; i++) // value range
			POS[i].clear(), q_dup[i] = 0;
		for (int i = 0; i < N; i++)
			POS[A[i]].push_back(i);
		for (int i = N-1; i >= 0; i--)
			belong[i] = i / PILE;
	}
	int compute_cnt(int x, int l, int r) {
		if (q_dup[x] == q_cases)
			return 0;
		q_dup[x] = q_cases;
		int va = (int) (lower_bound(POS[x].begin(), POS[x].end(), l) - POS[x].begin()) - 1;
		int vb = (int) (upper_bound(POS[x].begin(), POS[x].end(), r) - POS[x].begin()) - 1;
		return vb - va;
	}
	void query(int l, int r, int &a, int &b) {
		static int t;
		q_cases++;
		a = b = 0;
		if (belong[l] == belong[r]) {
			for (int i = l; i <= r; i++) {
				t = compute_cnt(A[i], l, r);
				if (t > a)	a = t, b = 0;
				if (t == a)	b++;
			}	
			return ;		
		}
		for (int i = belong[l]+1; i < belong[r]; i++) {
			for (int j = 0; j < Vmode[i].size(); j++) {
				t = compute_cnt(Vmode[i][j], l, r);
				if (t > a)	a = t, b = 0;
				if (t == a)	b++;
			}
		}
		for (int i = (belong[a]+1)*PILE-1; i >= l; i--) {
			t = compute_cnt(A[i], l, r);
			if (t > a)	a = t, b = 0;
			if (t == a)	b++;
		}
		for (int i = (belong[b])*PILE; i <= r; i++) {
			t = compute_cnt(A[i], l, r);
			if (t > a)	a = t, b = 0;
			if (t == a)	b++;
		}
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
			printf("%d %d\n", a, b);
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
