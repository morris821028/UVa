#include <bits/stdc++.h>
using namespace std;
int used[128];
void dfs(int A[], int idx, int n, long long S, long long T, long long &ret) {
	if (ret > S && S >= T)
		ret = S;
	if (ret == T)
		return ;
	if (idx == n)
		return ;
	for (int i = 0, prev = -1; i < n; i++) {
		if (A[i] == prev)
			continue;
		if (used[i])
			continue;
		used[i] = 1;
		dfs(A, idx+1, n, S+A[i], T, ret); 
		if (S > A[i])
			dfs(A, idx+1, n, S-A[i], T, ret); 
		dfs(A, idx+1, n, S*A[i], T, ret); 
		if (S%A[i] == 0)
			dfs(A, idx+1, n, S/A[i], T, ret); 
		prev = A[i];
		used[i] = 0;
	}
}
int main() {
	char line[1024];
	while (fgets(line, 1024, stdin)) {
		stringstream sin(line);
		long long T;
		sin >> T;
		if (T == 0)
			return 0;
		int n = 0, A[1024];
		while (sin >> A[n])
			n++;
		sort(A, A+n);
		long long ret = 1LL<<62;
		dfs(A, 0, n, 0, T, ret);
		if (ret == 1LL<<62)
			puts("0");
		else
			printf("%lld\n", ret);
	}
	return 0;
}
/*
15  6  3  2  5  20  3
15  20  5  6  3  3  2
15  5  6  3  3  2
10  1  2  3
8  6  4  5
14  4  3  7  5
11  3  3  3
6  3  3
0
*/
