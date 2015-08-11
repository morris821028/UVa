#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
class D2RMQ {
public:
	struct Node {
	    short mxv;
	};
	struct D2Tree {
	    Node subtree[2048];
	} d2tree[2048];
	int Mmain, Msub;
	short ansMax;
	void init(int n, int m) {
		for (Mmain = 1; Mmain < n+2; Mmain <<= 1);
        for (Msub = 1; Msub < m+2; Msub <<= 1);
        build();
	}
	void build() {
	    for (int i = (Mmain<<1)-1; i > 0; i--)
	        sub_build(i);
	}
	void modify(int x, int y, int val) {
	    static int s, t;
	    d2tree[x+Mmain].subtree[y+Msub].mxv = val;
	    t = x+Mmain;
	    for (s = (y+Msub)>>1; s > 0; s >>= 1)
	        d2tree[t].subtree[s].mxv = max(d2tree[t].subtree[s<<1].mxv, d2tree[t].subtree[s<<1|1].mxv);
	    for (s = (x+Mmain)>>1; s > 0; s >>= 1)
	        sub_modify(s, y);
	}
	void query(int lr, int rr, int lc, int rc) {
	    static int s, t;
		ansMax = 0;
		if (lr <= rr && lc <= rc)
	    for (s = lr+Mmain-1, t = rr+Mmain+1; (s^t) != 1;) {
	        if (~s&1)
	            sub_query(s^1, lc, rc);
	        if (t&1)
	            sub_query(t^1, lc, rc);
	        s >>= 1, t >>= 1;
	    }
	}	
private:
	void sub_build(int k) {
		memset(d2tree[k].subtree, 0, sizeof(Node) * Msub * 2);
//	    for (int i = (Msub<<1)-1; i > 0; i--)
//	        d2tree[k].subtree[i].mxv = 0;
	}
	void sub_modify(int k, int y) {
	    for (int s = y+Msub; s > 0; s >>= 1)
	        d2tree[k].subtree[s].mxv = max(d2tree[k<<1].subtree[s].mxv, d2tree[k<<1|1].subtree[s].mxv);
	}
	void sub_query(int k, int lc, int rc) {
	    static int s, t;
	    for (s = lc+Msub-1, t = rc+Msub+1; (s^t) != 1;) {
	        if (~s&1)
	            ansMax = max(ansMax, d2tree[k].subtree[s^1].mxv);
	        if (t&1)
	            ansMax = max(ansMax, d2tree[k].subtree[t^1].mxv);
	        s >>= 1, t >>= 1;
	    }
	}
} tool; 
char s1[1024], s2[1024];
char ss[32767];
int main() {
	int testcase, cases = 0;
	while (scanf("%s %s", s1+1, s2+1) == 2) {
		scanf("%d", &testcase);
		int n = strlen(s1+1), m = strlen(s2+1);
		int gap[256] = {};
		
		while (testcase--) {
			int GLCS = 0;
			for (int i = 0; i < 256; i++)
				gap[i] = 0x3f3f3f3f;
			while (scanf("%s", ss) == 1 && ss[0] != '$')
				scanf("%d", &gap[ss[0]]);
				
			tool.init(n, m);
			
			int K, lx, ly, rx, ry, dp;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (s1[i] == s2[j]) {
						K = gap[s1[i]];
						lx = max(i-K-1, 1), ly = max(j-K-1, 1);
						rx = i-1, ry = j-1;
						
						tool.query(lx, rx, ly, ry);
						dp = tool.ansMax+1;
						tool.modify(i, j, dp);
						GLCS = max(GLCS, dp);
					}
				}
			}
			printf("%d", GLCS);
			if (testcase)
				printf(" ");
		}
		puts("");
	}
	return 0;
}
/*
ACBDCAA ADDBCDBAC
2
A 2 B 2 C 2 D 2 $
A 1 B 1 C 1 D 1 $
$
A 2 B 0 C 3 D 0 $
*/ 
