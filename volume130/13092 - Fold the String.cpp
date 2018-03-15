#include <bits/stdc++.h>
using namespace std;
const int MAXS = 1048576;
char s[MAXS];
void manacher(char s[], int n, int dp[]) {
	static char t[MAXS<<1];
	int m = 2*n+1;
	t[0] = '$', t[m] = '#', t[m+1] = '\0'; 
	for (int i = 0; i < n; i++)
		t[i*2+1] = '#', t[i*2+2] = s[i];
	int mx = 0, idx = 0;
	for (int i = 1; i < m; i++) {
		if (mx > i)
			dp[i] = min(dp[2*idx-i], mx-i);
		else
			dp[i] = 1;
		int v = dp[i];
		while (t[i-v] == t[i+v])
			v++;
		dp[i] = v;
		if (v+i > mx)
			mx = v+i, idx = i;
	}
}
int main() {
	int testcase, cases = 0;
	int x, y;
	static int dp[MAXS<<1];
	static int dp2[MAXS];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &x, &y);
		scanf("%s", s);
		int n = strlen(s);
		manacher(s, n, dp);
//		for (int i = 3; i < 2*n+2; i += 2)
//			printf("[%02d] %c %c %d\n", i/2, s[i/2-1], s[i/2], dp[i]/2);
		for (int i = 3; i < 2*n; i += 2)
			dp[i/2-1] = dp[i]/2;
		
		queue<int> q;
		dp2[0] = 0;
		for (int i = 0; i < n; i++) {
			dp2[i+1] = dp2[i]+x;
			q.push(i);
			while (q.front() + dp[q.front()] < i)
				q.pop();
			int leftmost = q.front();
			dp2[i+1] = min(dp2[i]+x, dp2[leftmost+1]+y);
		}

		printf("Case %d: %d\n", ++cases, dp2[n]);
	}
	return 0;
}
/*
2
2  1
aabbaa
1  1
aabbaabba
*/
