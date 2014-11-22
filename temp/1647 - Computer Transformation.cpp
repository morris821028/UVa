#include <stdio.h>   

int A[1024][128] = {}; // A[i] = 2^(i-1)
int B[1024][128] = {}; // B[i] = B[i-2] + A[i-2], #00 = #1 in (i-2)th items and #00 in (i-2)th items.
int main(){
    A[0][0] = A[1][0] = 1;  
    for (int i = 2; i < 1024; i++) {
    	for (int j = 0; j < 127; j++) {
    		A[i][j] += A[i-1][j] + A[i-1][j];
    		B[i][j] += B[i-2][j] + A[i-2][j];
    		A[i][j+1] += A[i][j]/10000, A[i][j] %= 10000;
    		B[i][j+1] += B[i][j]/10000, B[i][j] %= 10000;
    	}
    }
    int n;
    while (scanf("%d", &n) == 1) {
    	int i = 127;
    	while (i > 0 && B[n][i] == 0)
    		i--;
    	printf("%d", B[n][i]);
    	for (i--; i >= 0; i--)
    		printf("%04d", B[n][i]);
    	puts("");
    }
    return 0;      
}
