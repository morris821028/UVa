#include <stdio.h>

int main() {
	int n, m, cases = 0;
	while(scanf("%d;%d", &n, &m) == 2) {
		if(cases++)	puts("");
		int signature = (n + 3)/4;
		if(signature%m)
			signature = signature / m + 1;
		else
			signature = signature / m;
		
		int base = 0;
		for(int i = 1; i <= signature; i++) {
			printf("signature %d\n", i);
			int page = m * 4;
			for(int j = 1; j <= m; j++) {
				printf(" sheet %d: pages %d and %d (front); pages %d and %d (back)\n", 
					j, j*2 + base, page - j*2 + 1 + base, page - j*2 + 2 + base, j*2 - 1 + base);
			}
			base += page;
		}
	}
	return 0;
}
/*
9;2
*/
