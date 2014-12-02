#include <stdio.h>
#include <algorithm>
using namespace std;
	
pair<int, int> A[100000];
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		long long sum = 0;
		int ret[100000] = {};
		for (int i = 0; i < n; i++) {
			scanf("%d", &A[i].first);
			A[i].second = i;
			sum += A[i].first;
		} 
		if (sum%2) {
			puts("No");
		} else {
			puts("Yes");
			sum /= 2;
			sort(A, A+n);
			for (int i = n-1; i >= 0; i--) {
				if (sum >= A[i].first)
					sum -= A[i].first, ret[A[i].second] = 1;
				else
					ret[A[i].second] = -1;
			}
			for (int i = 0; i < n; i++)
				printf("%d%c", ret[i], i == n-1 ? '\n' : ' ');
		}
	}
	return 0;
}
