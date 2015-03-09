#include <stdio.h>
#include <string.h>
#define min(a,b) (a) < (b) ? (a) : (b)
#define maxL 1048576
char a[maxL], b[maxL];
int dp[maxL];
int la, lb;
void solve() {
    int i, j, k;
    int mx = 0, idx = 0;
    int ans = 0;
    memset(dp, 0, sizeof(dp));
    for(i = 1; i < lb; i++) {
        if(mx > i)
            dp[i] = min(dp[2*idx-i], mx-i);
        else
            dp[i] = 1;
        for(; b[i-dp[i]] == b[i+dp[i]]; dp[i]++);

        if(dp[i]+i > mx)    mx = dp[i]+i, idx = i;
        if(dp[i] > ans) ans = dp[i];
    }
    printf("%d\n", ans-1);
}
int main() {
	int t, i;
	scanf("%d", &t);
	while(t--) {
		scanf("%s", a);
		la = strlen(a);
		b[0] = '$';
		for(i = 0; i < la; i++)
            b[i*2+1] = '#', b[i*2+2] = a[i];
        lb = 2*i+1, b[lb] = '#', b[lb+1] = '\0';
        solve();
	}
    return 0;
}
