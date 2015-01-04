#include <stdio.h> 
#include <algorithm>
using namespace std;

long long A[64], n, m;
int C[64][64] = {};
int calc(long long s, int i, int selected)  {
	if (selected > m || selected + i + 1 < m || s > A[i] * (i+1))	
		return 0;
	int ret = 0;
  	for (; i >= 0; i--) {
  		if (A[i] > s) {
  			if (selected + 1 + i >= m)
  				ret += C[i][m - (selected + 1)];
  		} else {
  			break;
  		}
  	}
  	for (; i > 0; i--)
  		ret += calc(s - A[i], i-1, selected + 1);
  	return ret;
}   
int main() {
	C[0][0] = 1;
	for (int i = 1; i < 64; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%lld", &A[i]);
		sort(A, A + n);

		int ret = 0;
		for (int i = 2; i < n; i++) {
			for (int j = i-1; j > 0; j--) {
				ret += calc(A[i] - A[j], j - 1, 2);
			}
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
7
4 3
10 10 20 20
6 4
1 1 1 1 1 1
4 3
10 20 30 100000000
6 6
2 3 4 5 6 7
6 4
1 2 6 7 10 12 
30 15
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
20 10
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
*/
