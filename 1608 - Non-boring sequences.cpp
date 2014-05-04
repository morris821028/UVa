#include <stdio.h> 
#include <algorithm>
#include <map>
using namespace std;
int A[262144];
int NEXT[262144], PREV[262144];
map<int, int> R;
int dfs(int l, int r) {
	if(l >= r)	return 1;
	for(int i = 0; i <= (r-l+1)/2; i++) {
		if(NEXT[l+i] > r && PREV[l+i] < l)
			return dfs(l, l+i-1) && dfs(l+i+1, r);
		if(NEXT[r-i] > r && PREV[r-i] < l)
			return dfs(l, r-i-1) && dfs(r-i+1, r);
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
