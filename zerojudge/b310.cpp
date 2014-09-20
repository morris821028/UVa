#include <stdio.h>
#include <algorithm>
using namespace std;

int A[1048576];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2)	 {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		int left = 0, sum = 0;
		int ret = 0x3f3f3f3f;
		for (int i = 0; i < n; i++) {
			sum += A[i]; 
			while (sum - A[left] >= m)
				sum -= A[left], left++;
			if (sum >= m)
				ret = min(ret, i - left + 1);
		}
		if (ret == 0x3f3f3f3f)
			puts("GGGGGZ");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
6 8
1 3 2 4 0 3
*/
