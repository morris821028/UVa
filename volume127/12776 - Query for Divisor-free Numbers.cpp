#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define maxL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[32767], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
vector< pair<int, int> > factor(int n) {
	int on = n;
	vector< pair<int, int> > R;
	
	for(int i = 0, j; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {		
			for(j = 0; n%P[i] == 0; n /= P[i], j++);
			R.push_back(make_pair(P[i], j));
		}
	}
	if(n != 1)	R.push_back(make_pair(n, 1));
	return R;
}
void make(int idx, int n, int m, vector< pair<int, int> > &v, vector<int> &ret) {
	if(idx == v.size()) {
		ret.push_back(m);
		return;
	}
	int a = m, b = v[idx].first;
	for(int i = v[idx].second; i >= 0; i--)
		make(idx + 1, n, a, v, ret), a *= b;
}
int A[131072], L[131072], R[131072];
vector<int> Af[131072], RM[131072];
vector< pair<int, int> > Q[131072], QL[131072];
int OUT[131072];
int BIT[131072];
void modify(int x, int val, int L) {
	while (x <= L) {
		BIT[x] += val;
		x += (x)&(-x);
	}
}
int query(int x) {
	int ret = 0;
	while (x) {
		ret += BIT[x];
		x -= (x)&(-x);
	}
	return ret;
}
int main() {
//		freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
	sieve();
	int testcase, cases = 0;
	int n, m, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &A[i]);
			vector< pair<int, int> > f = factor(A[i]);
			Af[i].clear();
			make(0, A[i], 1, f, Af[i]);
		}
		for (int i = 0; i < n + 20; i++)
			Q[i].clear(), QL[i].clear(), RM[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			Q[x].push_back(make_pair(y, i));
		}
		map<int, int> mp;
		map<int, int>::iterator mpit;
		for (int i = 1; i <= n; i++) {
			x = 0;
			for (int j = 0; j < Af[i].size(); j++)
				x = max(x, mp[Af[i][j]]);
			mp[A[i]] = i;
			L[i] = x + 1;
		}
		mp.clear();
		for (int i = n; i >= 1; i--) {
			x = n + 1;
			for (int j = 0; j < Af[i].size(); j++) {
				mpit = mp.find(Af[i][j]);
				if (mpit != mp.end())
					x = min(x, mpit->second);
			}
			mp[A[i]] = i;
			R[i] = x - 1;
		}
		for (int i = 1; i <= n; i++) {
			QL[L[i]].push_back(make_pair(R[i], i));
			RM[i].push_back(R[i]);
		}
		for (int i = 1; i <= n + 20; i++)
			BIT[i] = 0;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j < QL[i].size(); j++) {
				modify(QL[i][j].second, 1, n + 20);
				modify(QL[i][j].first + 1, -1, n + 20);
//				printf("add [%d %d]\n", QL[i][j].second, QL[i][j].first);
			}
			if (i)
			for (int j = 0; j < RM[i-1].size(); j++) {
				modify(i-1, -1, n + 20);
				modify(RM[i-1][j] + 1, 1, n + 20);
//				printf("rm [%d %d]\n", i-1, RM[i][j]);
			}
			for (int j = 0; j < Q[i].size(); j++) {
				int v = query(Q[i][j].first);
				OUT[Q[i][j].second] = v;
//				printf("%d %d - %d\n", Q[i][j].first, Q[i][j].second, v);
			}
//			puts("--");
		}
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < m; i++)
			printf("%d\n", OUT[i]);
	}
	return 0;
}
/*
2
10 5
4 6 2 7 5 11 14 21 13 2
2 6
4 8
2 8
3 7
4 9
5 3
4 6 8 1 5
1 5
2 3
3 3
*/
