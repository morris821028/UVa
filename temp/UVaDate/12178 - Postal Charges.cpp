#include <stdio.h> 
#include <vector>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;

int parseFloat() {
	static char s[32];
	scanf("%s", s);
	int x = 0, d = 0;
	for (int i = 0; s[i]; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			x = x * 10 + s[i] - '0';
		} else {
			for (i++; s[i]; i++)
				x = x * 10 + s[i] - '0', d++;
			break;
		}
	}
	while (d < 8)
		x *= 10, d++;
	return x;
}
int main() {
	const int gap = 1e+8;
	int n;
	long long x, y;
	while (scanf("%d", &n) == 1) {
		vector< pair<long long, long long> > A[16][16];
		long long sumX[16][16] = {}, sumY[16][16] = {};
		long long sum2X[16][16] = {}, sum2Y[16][16] = {};
		long long sumN[16][16] = {};
		for (int i = 0; i < n; i++) {
			x = parseFloat();
			y = parseFloat();
			A[x/gap][y/gap].push_back(make_pair(x, y));
			sumX[x/gap][y/gap] += x, sumY[x/gap][y/gap] += y;
		}
		
		for (int i = 0; i < 16; i++) {
			long long sx = 0, sy = 0;
			long long cnt = 0;
			for (int j = 0; j < 16; j++) {
				sx += sumX[i][j];
				sum2X[i][j] = sum2X[i-1][j] + sx;
				sy += sumY[i][j];
				sum2Y[i][j] = sum2Y[i-1][j] + sy;
				cnt += A[i][j].size();
				sumN[i][j] = sumN[i-1][j] + cnt;
			}
		}
		
		double v = 0, vn = 0;
		for (int i = 1; i < 16; i++) {
			for (int j = 1; j < 16; j++) {
				for (int k = 0; k < A[i][j].size(); k++) {
					v += A[i][j][k].first * sumN[i-1][j-1] - sum2X[i-1][j-1];
					v += A[i][j][k].second * sumN[i-1][j-1] - sum2Y[i-1][j-1];
					vn += sumN[i-1][j-1];
				}
			}
		}
		printf("%.8lf\n", v / vn / 1e+8);
	}
	return 0;
}
/*
2
0 0
1 1

4
0 0
1.5 1.7
1.5 1.7
0 0

3
0.2 0.2
1.2 1.2
2.3 0.5

6
2 1
0 0
0 1.5
1.2 1.2
2.5 2.1
0.5 1.7 
*/
