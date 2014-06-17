#include <stdio.h> 
// TLE WTF
#include <algorithm>
#include <map>
using namespace std;
int A[262144];
int NEXT[262144], PREV[262144];
map<int, int> R;
int dfs(int l, int r) {
	if(l >= r)	return 1;
	int m = (l+r)/2;
	for(int i = m, j = m; i >= l && j <= r; i--, j++) {
		if(NEXT[i] > r && PREV[i] < l)
			return dfs(l, i-1) && dfs(i+1, r);
		if(NEXT[j] > r && PREV[j] < l)
			return dfs(l, j-1) && dfs(j+1, r);
	}
	return 0;
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &A[i]);
			NEXT[i] = n+1;
			PREV[i] = 0;
		}
		R.clear();
		for(int i = 1; i <= n; i++) {
			PREV[i] = R[A[i]], NEXT[PREV[i]] = i;
			R[A[i]] = i;
		}
		puts(dfs(1, n) ? "non-boring" : "boring");
	}
	return 0;
}
/*
20
6
1 2 3 1 2 3
5
1 2 3 4 5
5
1 1 1 1 1
5
1 2 3 2 1
5
1 1 2 1 1
*/
