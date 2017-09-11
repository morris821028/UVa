#include <bits/stdc++.h> 
using namespace std;

// find ax + by = g
void exgcd(int64_t x, int64_t y, int64_t &g, int64_t &a, int64_t &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
// solve a x = b (mod n), n > 0
void mod_linear(int64_t a, int64_t b, int64_t n, 
					set<int64_t> &ret, int64_t X, int64_t r1, int64_t N) {
	int64_t x, y, d;
	exgcd(a, n, d, x, y);
	if (b%d != 0)
		return ;
	int64_t s = n/d;
	x = (x*(b/d)%s + s)%s;
	// x, x+(n/d), x+2*(n/d), ...
	int64_t r2 = a*x - r1;
	int64_t gap = a*n/d; 
	if (r2 < 0)	r2 += (-r2/gap + 1)*gap;
	while (r2 < N) {
		if (r2*r2%N == X)
			ret.insert(r2);
		r2 += gap;
	}
	return ;
}

// r^2 = x mod N
// 	r_1^2 + k_1 N = x   --- (1)
// 	r_2^2 + k_2 N = x   --- (2)
// 
// 	(1)-(2) 
//		=> r_1^2 - r_2^2 = N (k_2 - k_1)
//		=> (r_1 + r_2)(r_1 - r_2) = AB (k_2 - k_1)
//		=> r_1 + r_2 = A K_1
//		   r_1 - r_2 = B K_2
//			=> A K_1 = 2 r_1 (mod B)
//			   r_2 = K_1 A - r_1

int main() {
	int cases = 0;
	int64_t x, N, r1;
	while (scanf("%lld %lld %lld", &x, &N, &r1) == 3 && N) {
		set<int64_t> ret;
		x %= N;
		for (int64_t A = 1; A*A <= N; A++) {
			if (N%A == 0) {
				mod_linear(A, 2*r1, N/A, ret, x, r1, N);
				mod_linear(N/A, 2*r1, A, ret, x, r1, N);
			}
		}
		
		printf("Case %d:", ++cases);
		for (auto e: ret)
			printf(" %lld", e);
		puts("");
	}
	return 0;
}
/*
1 12 1
4 15 2
*/
