#include <stdio.h> 
int A[1048576];
int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		A[1] = 3, A[2] = 1;
		for(int i = 3; i <= n; i += 2)
			A[i] = i + 2;
		if(n%2) {
			A[n] = n - 1;
			for(int i = n-1; i > 2; i -= 2)
					A[i] = i - 2;
		} else {
			A[n] = n-2, A[n-1] = n;
			for(int i = n-2; i > 2; i -= 2)
					A[i] = i - 2;
		}
		printf("%d", A[1]);
		for(int i = 2; i <= n; i++)
			printf(" %d", A[i]);
		puts("");
	}
	return 0;
}
