#include <bits/stdc++.h> 
using namespace std;

int main() {
	int J, R, x;
	while (scanf("%d %d", &J, &R) == 2) {
		int S[512] = {}, L[512] = {};
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < J; j++)
				scanf("%d", &x), S[j] += x, L[j] = x;
		}
		int ret = 0;
		for (int i = 1; i < J; i++) {
			if (S[i] > S[ret] || (S[i] == S[ret] && L[i] >= L[ret]))
				ret = i;
		}
		printf("%d\n", ret+1);
	}
	return 0;
}
