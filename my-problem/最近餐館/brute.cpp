#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;
int pt[8192][10], Q[10];
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("brute_out.txt", "w+t", stdout); 
	int n, m, x, q;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &pt[i][j]);
		scanf("%d", &q);
		while (q--) {
			for (int i = 0; i < m; i++)
				scanf("%d", &Q[i]);
			scanf("%d", &x);
			printf("Case %d: %d", ++cases, x);
			vector< pair<int, int> > D;
			for (int i = 0; i < n; i++) {
				int dist = 0;
				for (int j = 0; j < m; j++)
					dist += (Q[j] - pt[i][j]) * (Q[j] - pt[i][j]);
				D.push_back(make_pair(dist, i));
			}
			sort(D.begin(), D.end());
			for (int i = 0; i < x && i < D.size(); i++)
				printf(" %d", D[i].second + 1);
			puts("");
		}
	}
	return 0;
}
