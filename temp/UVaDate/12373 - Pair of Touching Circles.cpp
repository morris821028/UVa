#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;
// http://en.wikipedia.org/wiki/Pythagorean_triple
vector<int> A, B, C;
long long D[1024][1024] = {};
void pythagorean_triple() {
	for (int n = 1; n < 32; n++) {
		for (int m = n+1; m < 32; m += 2) {
			if (__gcd(n, m) > 1)
				continue;
			if (n * n + m * m > 1000)
				continue;
			int a = m * m - n * n;
			int b = 2 * m * n;
			int c = m * m + n * n;
			A.push_back(a);
			B.push_back(b);
			C.push_back(c);
		}
	}
}
void build_oblique() {
	for (int i = 0; i < A.size(); i++) {
		int a = A[i], b = B[i], c = C[i];
		while (a <= 1000 && b <= 1000) {
			for (int r1 = 1; r1 < c; r1++) {
				int r2 = c - r1;
				int w = r1 + r2 + a, h = r1 + r2 + b;
				w = max(w, max(r1 * 2, r2 * 2));
				h = max(h, max(r1 * 2, r2 * 2));
				if (w <= 1000 && h <= 1000) {
					D[w][h] += 2;
					D[h][w] += 2;
				}
			}
			a += A[i], b += B[i], c += C[i];
		}
	}
}
	
int main() {
	pythagorean_triple();
	build_oblique();
	int testcase, cases = 0;
	int H, W;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &H, &W);
		int N = max(H, W)/2, w, h;
		long long ret = 0;
		
		// horizontal & vertical
		for (int r1 = 1; r1 <= N; r1++) {
			for (int r2 = 1; r2 <= N; r2++) {
				w = max(r1, r2) * 2, h = (r1 + r2) * 2;
				if (w <= W && h <= H)
					ret += (long long) (W - w + 1) * (H - h + 1);
				h = max(r1, r2) * 2, w = (r1 + r2) * 2;
				if (w <= W && h <= H)
					ret += (long long) (W - w + 1) * (H - h + 1);
			}
		}
		
		// oblique
		for (int i = 1; i <= H; i++) {
			for (int j = 1; j <= W; j++) {
				ret += D[i][j] * (H - i + 1) * (W - j + 1);
			}
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
999
10 10
20 20
100 100
1000 1000

5
4 2
4 3
4 4
4 6
10 10
*/
