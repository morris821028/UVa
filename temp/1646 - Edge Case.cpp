#include <stdio.h> 
#include <stdlib.h>
int A[10024][535] = {};

int main() {
	int n;    
	A[1][0] = 1, A[2][0] = 3;
    for (int i = 3; i < 10024; i++) {
    	for (int j = 0; j < 530; j++) {
    		A[i][j] += A[i-1][j] + A[i-2][j];
    		A[i][j+1] += A[i][j]/10000, A[i][j] %= 10000;
    	}
    }
    while (scanf("%d", &n) == 1) {
    	int i = 530;
    	while (i > 0 && A[n][i] == 0)
    		i--;
    	printf("%d", A[n][i]);
    	for (i--; i >= 0; i--)
    		printf("%04d", A[n][i]);
    	puts("");
    }
//	while (scanf("%d", &n) == 1) {
//		int ret = 0;
//		for (int i = (1<<n) - 1; i >= 0; i--) {
//			int ok = 1;
//			for (int j = 0; j < n; j++) {
//				if (((i>>j)&1) && ((i>>((j+1)%n))&1))
//					ok = 0;
//			}
//			if (ok == 0)	continue;
//			ret += ok;
//		}
//		printf("%d\n", ret);
//	}
	return 0;
}
