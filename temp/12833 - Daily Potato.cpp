#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXL 262144
char S[MAXL], C[MAXL], T[MAXL];
int dp[MAXL], n, m;
int A[MAXL][26], SUM[MAXL][26];
void exbuild(char S[]) { // manacher's algorithm
	n = strlen(S), m = 2 * n + 1;
    int mx = 0, idx = 0;
    int ans = 0;
	T[0] = '$', T[m] = '#', T[m + 1] = '\0';
	for (int i = 0; i < n; i++)
    	T[i * 2 + 1] = '#', T[i * 2 + 2] = S[i];
    //
    memset(SUM[0], 0, sizeof(SUM[0]));
    for (int i = 1; i < m; i++) {
    	memcpy(SUM[i], SUM[i-1], sizeof(SUM[0]));
    	if ('a' <= T[i] && T[i] <= 'z')
    		SUM[i][T[i] - 'a']++;
    }
    //
    for (int i = 1; i < m; i++) {
        if (mx > i) {
        	memcpy(A[i], A[2 * idx - i], sizeof(A[2 * idx - i]));
            dp[i] = min(dp[2 * idx - i], mx - i);
            if (dp[2 * idx - i] >= mx - i) {
            	int r = idx - (mx - idx), l = 2 * idx - i - dp[2 * idx - i];
            	for (int j = 0; j < 26; j++) {
            		A[i][j] -= (SUM[r][j] - SUM[l][j]) * 2;
            	}
        	}
        } else {
        	for (int j = 0; j < 26; j++)
        		A[i][j] = SUM[i][j] - SUM[i-1][j];
            dp[i] = 1;
        }
        for(; T[i-dp[i]] == T[i+dp[i]]; dp[i]++)
        	if ('a' <= T[i+dp[i]] && T[i+dp[i]] <= 'z')
				A[i][T[i-dp[i]] - 'a'] += 2;

        if(dp[i] + i > mx)		mx = dp[i] + i, idx = i;
    }
//    for (int i = 1, j = 0; i < m; i ++, j++)
//    	printf("[%02d] %c %d\n", i, T[i], dp[i]);
}
vector<int> pos[128];
vector<int> M[2][26];
void prepare() {
	for (int i = 0; i < 26; i++)
		M[0][i].clear(), M[1][i].clear();
//	for (int i = 0; i < 128; i++)
//		pos[i].clear();
//	for (int i = 1; i < m; i++) {
//		pos[T[i]].push_back(i);
//	}
	for (int i = 1; i < m; i++) {
//		printf("%c ", T[i]);
		for (int j = 0; j < 26; j++) {
			M[A[i][j]&1][j].push_back(A[i][j]);
//			printf("%d ", A[i][j]);
		}
//		puts("");
	}
	for (int i = 0; i < 26; i++) {
		sort(M[0][i].begin(), M[0][i].end());
		sort(M[1][i].begin(), M[1][i].end());
	}
}
void query(int x, char c) {
	if (x == 0)	{puts("0"); return;}
//	int sum = 0, front = 0, rear = 0;
//	int ret = 0, mid;
//	for (int i = x - 1, j = 0; i < pos[c].size(); i++, j++) {
//		front = pos[c][j], rear = pos[c][i];
//		mid = (front + rear)/2;
//		if (mid + dp[mid] - 1 >= rear)
//			ret++;
//	}
//	printf("%d\n", ret);
	int p = (int) (lower_bound(M[x&1][c - 'a'].begin(), M[x&1][c - 'a'].end(), x) - M[x&1][c - 'a'].begin());
	printf("%d\n", int(M[x&1][c - 'a'].size() - p));
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout); 
	int testcase, N, Q, cases = 0;
	int x;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %s", &N, S);
		scanf("%d %s", &Q, C);
		exbuild(S);
		prepare();
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < Q; i++) {
			scanf("%d", &x);
			query(x, C[i]);
		}
	}
    return 0;
}
/*
1
8
abccbaab
6
abcabc
2 2 2 1 1 3

1000
6
abaaba
7
aaaaaab
5 4 3 2 1 0 2

123
10
ccecabebcb
10
ebddcdacad
5 6 2 5 5 5 5 1 9 9
10
abbbbeaaba
10
cbabcabcec
2 0 1 8 5 6 2 4 8 1
10
baddaeaecb
10
bbdebdbedd
1 5 5 6 2 9 9 1 5 0
*/
