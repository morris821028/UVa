// http://mypaper.pchome.com.tw/zerojudge/post/1326837348
#include <stdio.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <ctype.h>
using namespace std;
int A[105], B[105];
int dp[105][105]; //[l][r][___{l, r}]
char used[105][105] = {}, usedcases = 0;
int dfs(int l, int r) {
    if(l > r)    return 0;
    if(used[l][r] == usedcases)
        return dp[l][r];
    int &ret = dp[l][r];
    used[l][r] = usedcases;
    if(A[l] == -1) {
    	ret = dfs(l + 1, r);
    	return ret;
    }
    ret = dfs(l+1, r) + 1;
    for(int i = l+1; i <= r && A[i] != -1; i++) {
        if(A[i] == A[l]) {
            ret = min(ret, dfs(l+1, i-1) + dfs(i, r));
        }
    }
    return ret;
}
int main() {
    int testcase, n, m;
    int cases = 0, i;
    char material[105][32];
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        
        map<string, int> R;
        for(int i = 0; i < n; i++) {
        	scanf("%s", material[i]);
        	if(islower(material[i][0]))
        		R[material[i]] = 0;
        }
        
        int size = 0;
        for(map<string, int>::iterator it = R.begin(); it != R.end(); it++)
        	it->second = size++;
        for(int i = 0; i < n; i++)	 {
        	if(isupper(material[i][0]))
        		A[i] = -1;
        	else
        		A[i] = R[material[i]];
        }
        
        for(i = 1, B[0] = 1, m = 0; i < n; i++) {
            if(A[m] == A[i])
                B[m]++;
            else {
                A[++m] = A[i], B[m] = 1;
            }
        }
        usedcases++;
        printf("Case %d: %d\n", ++cases, dfs(0, m));
    }
    return 0;
}
