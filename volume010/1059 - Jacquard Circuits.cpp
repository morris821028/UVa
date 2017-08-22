#include <bits/stdc++.h> 
using namespace std;

// Pick's theorem: A = i + b/2 - 1
int64_t llgcd(int64_t x, int64_t y) {
	if (y == 0)	return x;
	int64_t t;
	while (x%y) 
		t = x, x = y, y = t % y;
	return y;
}
int main() {
	const int MAXN = 1024;
	int cases = 0;
	int64_t n, m;
	int64_t p[MAXN][2];
	while (scanf("%lld %lld", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lld %lld", &p[i][0], &p[i][1]);
			
		// remove the collinear point
		{
			int del[MAXN] = {};
			for (int i = 0; i < n; i++) {
				int64_t c;
				int64_t px, py, qx, qy;
				px = p[(i+1)%n][0] - p[i][0], py = p[(i+1)%n][1] - p[i][1];
				qx = p[(i-1+n)%n][0] - p[i][0], qy = p[(i-1+n)%n][1] - p[i][1];
				c = px*qy - py*qx;
				if (c == 0)
					del[i] = 1;
			}
			
			int tn = 0;
			for (int i = 0; i < n; i++) {
				if (del[i] == 0)
					p[tn][0] = p[i][0], p[tn][1] = p[i][1], tn++;
			}
			n = tn;
			
			if (n < 3) {
				printf("Case %d: 0\n", ++cases);
				continue;
			}				
		}
		
		// normalize the lattice polygon to the origin one
		int64_t scale = 0;
		for (int i = 0, j = n-1; i < n; j = i++) {
			int64_t dx = p[i][0] - p[j][0];
			int64_t dy = p[i][1] - p[j][1];
			if (dx < 0)	dx = -dx;
			if (dy < 0) dy = -dy;
			
			if (dx)
				scale = scale ? llgcd(scale, dx) : dx;
			if (dy)
				scale = scale ? llgcd(scale, dy) : dy;
		}
		
		if (scale == 0)
			scale = 1;
		
		int64_t o_A = 0, o_b = 0;
		// origin area
		for (int i = 0, j = n-1; i < n; j = i++) 
			o_A += p[i][0]*p[j][1] - p[i][1]*p[j][0];
		if (o_A < 0)
			o_A = -o_A;
		o_A /= scale*scale;	// without /2 because the integer number
		
		// count the lattice point on the boundary except corner
		for (int i = 0, j = n-1; i < n; j = i++) {
			int64_t dx = p[i][0] - p[j][0];
			int64_t dy = p[i][1] - p[j][1];
			if (dx < 0)	dx = -dx;
			if (dy < 0) dy = -dy;
			
			dx /= scale, dy /= scale;
			o_b += llgcd(dx, dy);
		}
		
		// Pick's theorem: 2A = 2i + b - 2
		uint64_t sumA = m*(m+1)/2*(2*m+1)/3*o_A;
		uint64_t sumb = m*(m+1)/2*o_b;
		uint64_t sumi = (sumA + 2*m - sumb)/2;
		printf("Case %d: %llu\n", ++cases, sumi);
//		printf("-- %lld %lld\n", sumA, sumb);
//		printf("-- %lld %lld %lld, %lld\n", scale, o_A, o_b, sumA - sumb + 2 * m);
	}
	return 0;
}
/*

5 100
0 0
2 0
3 0
4 0
2 2

4 100
-100000 -100000
100000 -100000
100000 100000
-100000 1000007 
4 150
-100000 -100000
100000 -100000
100000 100000
-100000 1000007 

5  2
0  0
8  0
12  4
8  8
0  8

3  2
-1  -1
3  1
5  -1

8 86031
99 66
-93 -27
98 75
40 42
60 52
85 63
10 25
14 27

5 999999
2 2
2 3
2 4
3 4
4 4

3 999999
2 2
2 4
4 4

0 0

1333337666669333330999999000000
43333631666663331074999000000
1353402353299979900
10746818746599919800
18446744073709551616 


*/
