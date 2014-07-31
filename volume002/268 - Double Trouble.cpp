#include <stdio.h>
/* 
2*(NM) = MN, 0 <= M < B
2(N * B + M) = N + B^(k-1) * M
N = M * (B^(k-1) - 2)/(2 * B - 1)
*/
int main() {
	int B;
	while(scanf("%d", &B) == 1) {
		printf("For base %d the double-trouble number is\n", B);
		
		int d, product = 1, M;
		for(int k = 1; k < 1024; k++) {
			int ok = 0;
			for(M = 1; M < B; M++) {
				if((M * (product - 2))%(2 * B - 1) == 0) {
					ok = 1, d = k;
					break;
				}
			}
			if(ok)	break;
			product = (product * B)%(2 * B - 1);
		}
		
		int N[1024] = {};
		N[d - 1] = 1;
		for(int i = 0, carry = -2; i <= d; i++) {
			N[i] += carry;
			if(N[i] < 0) {
				N[i] += B, carry = -1;
			} else {
				break;
			}
		}
		
		for(int i = 0; i <= d; i++)
			N[i] *= M;
		for(int i = 0; i <= d; i++)
			N[i+1] += N[i]/B, N[i] %= B;
		for(int i = d, j = 0; i >= 0; i--) {
			j = j * B + N[i];
			N[i] = j / (2 * B - 1), j %= (2 * B - 1);
		}
		for(int i = d-2; i >= 0; i--)
			printf("%d ", N[i]);
		printf("%d \n", M);
	}
	return 0;
}
