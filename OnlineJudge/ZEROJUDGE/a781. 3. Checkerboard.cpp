#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		if (cases++)	puts("");
		for (int i = 0; i < 8; i++) {
			for (int p = 0; p < n; p++) {
				for (int j = 0; j < 8; j++) {
					for (int q = 0; q < n; q++)
						printf("%c", (i+j)%2 ? '.' : '#');
				}
				puts("");
			}
		}
	}
	return 0;
}
