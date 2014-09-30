#include <stdio.h> 
#include <map> 
#include <algorithm>
using namespace std;

int main() {
	int n, m, x, y, z;
	int A[512], B[512], C[512], D[512];
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d %d %d %d", A+i, B+i, C+i, D+i);
		map<unsigned int, int> R;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &z);
			unsigned int a = 63689, b = 378551;
			unsigned int value = 0;
			for (int j = 0; j < n; j++) {
				if (A[j] * x + B[j] * y + C[j] * z > D[j])
					value = value * a + 1;
				else
					value = value * a + 0;
				a *= b;
			}
			R[value]++;
		}
		int ret = 0;
		for (map<unsigned int, int>::iterator it = R.begin();
			it != R.end(); it++)
				ret = max(ret, it->second);
		printf("%d\n", ret);
	}
	return 0;
}
/*
2 5
1 0 0 1
2 0 0 8
0 1 0
2 2 2
3 3 3
5 5 5
2 18 4
4 8
0 0 1 1
1 0 1 2
-1 1 1 3
-1 -1 1 3
0 0 5
0 0 4
0 0 -2
1 0 5
40 19 104
13 26 84
89 -45 18
3 1 0
*/
