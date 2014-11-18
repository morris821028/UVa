#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int time[24] = {}, x;
		for (int i = 0; i < n; i++)
			scanf("%d", &x), time[x+11]++;
		for (int i = 0; i < 24; i++)
			time[i] = time[i]&1;
		int A[64], m = 0, ret = 0x3f3f3f3f;
		for (int i = 0; i < 24; i++)
			if (time[i])	A[m++] = i;
		for (int i = 0; i < m; i++)
			A[i + m] = A[i] + 24;
		if (m == 0)	ret = 0;
		for (int i = 0; i < m; i++) {
			int c = 0;
			for (int j = 0; j < m; j += 2)
				c += A[i+j+1] - A[i+j];
			ret = min(ret, c);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
6
-3 -10 -5 11 4 4
2
-6 6
8
0 0 0 0 0 0 0 0
*/
