#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int A[128] = {}, B[128] = {}, mx = 0;
		for (int i = 0; i < 128; i++)
			A[i] = -1;
		for (int i = 0; i < n; i++) {
			int x, w, h;
			scanf("%d %d %d", &x, &w, &h);
			for (int j = x; j <= x + w + 1; j++)
				A[j] = max(A[j], h);
			mx = max(mx, h);
		}
		
		for (int i = mx; i >= -1; i--) {
			for (int j = 1; j <= 50; j++) {
				if (A[j] == i) {
					if (A[j-1] < A[j] || A[j+1] < A[j]) {
						printf("+");
					} else {
						printf("-");
					}
				} else if (A[j] > i) {
					if (A[j-1] < A[j] || A[j+1] < A[j]) {
						if (B[j])
							printf(" ");
						else if (A[j+1] >= i && A[j-1] >= i)
							printf("+"), B[j] = 1;
						else if (i != -1)
							printf("|");
						else if (B[j] == 0)
							printf("+");
						else
							printf(" ");
					} else {
						printf(" ");
					}
				} else {
					printf(" ");
				}
			}
			puts("");
		}
		for (int i = 1; i <= 50; i++)
			printf("%d", i%10);
		puts("");
	}
	return 0;
}
