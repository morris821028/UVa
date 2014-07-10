#include <stdio.h> 

int main() {
	int K, cases = 0;
	while(scanf("%d", &K) == 1) {
		if(cases++)	puts("");
		int m = K-1;
		for(int i = 0; i < K; i++) {
			printf("%d", 1);
			for(int j = 1; j < K; j++)
				printf(" %d", i * m + j + 1);
			puts("");
		}
		
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < m; j++) {
				printf("%d", i+2);
				for(int s = 0; s < m; s++)
					printf(" %d", (j + s * i)%m + s*m + K + 1);
				puts("");
			}
		}
	}
	return 0;
}
