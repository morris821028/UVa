#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <functional>
using namespace std;
const char name[2][10] = {"Petra", "Jan"};

pair<int, int> D[1024];
pair<int, int> dp[1024][512];

bool cmp(pair<int, int> p, pair<int, int> q) {
	if(p.first != q.first)
		return p.first > q.first;
	return p.second < q.second;
}
int main() {	
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
	int testcase, n;
	char s[1024];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %s", &n, s);
		
		for(int i = 1; i <= n; i++) {
			int p, j;
			scanf("%d %d", &p, &j);
			D[i] = make_pair(p, j);
		}
		sort(D+1, D+1+n, cmp);
		
		int base = 0;
		if(!strcmp(name[0], s)) {
			base = D[1].first;
			for(int i = 1; i < n; i++)
				D[i] = D[i+1];
			n--;
		}
		memset(dp, 0, sizeof(dp));
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= (i+1)/2; j++) {
				dp[i][j] = make_pair(dp[i-1][j].first, dp[i-1][j].second + D[i].first);
				if(j)
					dp[i][j] = max(dp[i][j], 
						make_pair(dp[i-1][j-1].first + D[i].second, dp[i-1][j-1].second));
			}
		}
		printf("%d %d\n", dp[n][(n+1)/2].second + base, dp[n][(n+1)/2].first);
	}
	return 0;
}

/*
3
4
Petra
100 80
70 80
50 80
30 50
4
Petra
10 1
1 10
6 6
4 4
7
Jan
4 1
3 1
2 1
1 1
1 2
1 3
1 4
*/
