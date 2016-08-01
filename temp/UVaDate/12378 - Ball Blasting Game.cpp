// manacher's algorithm, maximum palindrome substring
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXL 262144
char S[MAXL], T[MAXL];
int dp[MAXL];
int exbuild(char S[]) { // manacher's algorithm
	int n = strlen(S), m = 2 * n + 1;
    int mx = 0, idx = 0;
    int ans = 0;
	T[0] = '$', T[m] = '#', T[m + 1] = '\0';
	for (int i = 0; i < n; i++)
    	T[i * 2 + 1] = '#', T[i * 2 + 2] = S[i];
    //
    for (int i = 1; i < m; i++) {
        if (mx > i) {
        	dp[i] = min(dp[2*idx-i], mx-i);
        } else {
            dp[i] = 1;
        }
		for(; T[i-dp[i]] == T[i+dp[i]]; dp[i]++);
		
        if(dp[i] + i > mx)		mx = dp[i] + i, idx = i;
    }
    
    int ret = 0;
    for (int i = 1, j = 0; i < m; i ++, j++) {
    	ret = max(ret, dp[i]);
//    	printf("[%02d] %c %d\n", i, T[i], dp[i]);
    }
    return ret;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", S);
		
		int n = strlen(S), m = 0;
		for (int i = 1; i < n; i++)
			if (S[i] != S[m])
				S[++m] = S[i];
		S[++m] = '\0';
		
		int mx_palindrome = exbuild(S); 
		printf("%d\n", mx_palindrome/2);
	}
	return 0;
}
/*
4
GGGBWWRRWRR
XAABCBAXAAAA
CCC
ABA
*/
