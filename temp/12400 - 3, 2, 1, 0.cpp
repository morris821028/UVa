#include <stdio.h> 
#include <string.h>
using namespace std;
// 2 * 10^(n-1) = 5^(n-1) * 2^n
// 3 * 10^(n-1) = 3 * 5^(n-1) * 2^(n-1)
#define MAXN 1024
int C[MAXN] = {};
int A[MAXN][MAXN] = {}, B[MAXN][MAXN] = {};
char s[MAXN];
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	A[0][0] = 1, B[0][0] = 1, B[0][1] = 1;
	// A[i] : binary for 5^i, B[i] : binary for 3 * 5^i
	for (int i = 1; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			A[i][j] = A[i-1][j] * 5;
			B[i][j] = B[i-1][j] * 5;
		}
		for (int j = 0; j < MAXN - 1; j++) {
			A[i][j+1] += A[i][j] / 2;
			A[i][j] &= 1;
			B[i][j+1] += B[i][j] / 2;
			B[i][j] &= 1;
		}
	}
	for (int i = 0; i < MAXN; i++) {
		if (C[i]%2 == 0) { // add 2
			for (int j = i + 1, k = 0; j < MAXN; j++, k++)
				C[j] += A[i][k];
//			printf("2");
			s[i] = '2';
		} else { // add 3
			for (int j = i, k = 0; j < MAXN; j++, k++)
				C[j] += B[i][k];
			s[i] = '3';
//			printf("3");
		}
		C[i+1] += C[i] / 2;
		C[i] &= 1; 
	}
	int n, m, k;
	while (scanf("%d %d %d", &n, &m, &k) == 3) {
		int a = 0, b = 0;
		for (int i = 0; i < k; i++) {
			a += s[i] == '3';
			b += s[i] == '2';
		}
//		printf("%d %d\n", a, b);
		if (n >= a && m >= b) {
			for (int i = k - 1; i >= 0; i--)
				putchar(s[i]);
			puts("");
		} else {
			puts("Impossible.");
		}
	}
	return 0;
}
