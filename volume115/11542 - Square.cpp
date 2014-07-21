#include <stdio.h> 
#include <algorithm>
using namespace std;
#define maxL (500>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[505], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 500;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i; 
        }
    }
}
int main() {
	sieve();
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		
		int f[505][505] = {};
		long long x;
		for(int i = 0; i < n; i++) {
			scanf("%lld", &x);
			for(int j = 0; j < Pt; j++)
				while(x%P[j] == 0)
					x /= P[j], f[j][i] ^= 1;
		}
		// xor gauss
		int row = Pt, col = n, arb = 0;
		for(int r = 0, c = 0; r < row && c < col; c++) {
			int k = r;
			for(int j = r + 1; j < row; j++)
				if(f[j][c])	k = j;
			for(int j = 0; j < col; j++)
				swap(f[r][j], f[k][j]);
				
			if(f[r][c] == 0) {arb++;continue;}
			
			for(int j = 0; j < row; j++) {
				if(r == j)	continue;
				if(f[j][c]) {
					for(int k = col; k >= c; k--)
						f[j][k] = f[j][k] ^ f[r][k];
				}
			}
			r++;
		}
		printf("%lld\n", (1LL<<arb) - 1);
	}
	return 0;
}
