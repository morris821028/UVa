#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 1<<23; 
class zkwRMQ {
public:
	int N, M;
	unsigned int A[MAXN], tree[MAXN<<1];
	void init(int n) {
		N = n;
		for (M = 1; M < N+2; M <<= 1);
	} 
	void build() {
    	for (int i = 2*M-1; i > 0; i--) {
        	if (i >= M)
            	tree[i] = A[i-M];
        	else
            	tree[i] = max(tree[i<<1], tree[(i<<1)+1]);
    	}
	}
	unsigned int query(int s, int t) {
	    unsigned int ret = 0;
	    for (s = s+M-1, t = t+M+1; (s^t) != 1;) {
	        if (~s&1)
	            ret = max(ret, tree[s^1]);
	        if (t&1)
	            ret = max(ret, tree[t^1]);
	        s >>= 1, t >>= 1;
	    }
	    return ret;
	}
} tool; 
unsigned int seed = 0;
unsigned int mrandom() {
    return seed = ( seed * 9301 + 49297);
}
int main() {
	int N, M, S, x, y;
	while (scanf("%d %d %d", &N, &M, &S) == 3) {
		seed = S;
		tool.init(N);
    	for (int i = 1; i <= N; i++)
    		tool.A[i] = mrandom();
    	tool.build();
        unsigned int ans = 0;
        for (int i = 0; i < M; i++) { 
        	x = mrandom()%N+1, y = mrandom()%N+1;
            if(x > y)  swap(x, y); 
            ans ^= tool.query(x, y);
        } 
        printf("%lu\n", ans);
    }    
	return 0;
}
