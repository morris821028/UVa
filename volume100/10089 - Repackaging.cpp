#include <stdio.h> 
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int main() {
	int n, S1, S2, S3;
	const double pi = acos(-1);
	while(scanf("%d", &n) == 1 && n) {
		double A[1024];
		for(int i = 0; i < n; i++) {
			scanf("%d %d %d", &S1, &S2, &S3);
			A[i] = atan2(S2 - S1, S3 - S1);
		}
		sort(A, A + n);
		double gap = 0;
		for(int i = 1; i < n; i++) {
			gap = max(gap, A[i] - A[i-1]);
		}
		gap = max(gap, 2 * pi - (A[n-1] - A[0]));
		puts(gap > pi ? "No" : "Yes");
	}
	return 0;
}
