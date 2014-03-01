#include <stdio.h>
#include <stdlib.h>
int main() {
	long long A, L, TA;
	int Case = 0;
	while(scanf("%lld %lld", &A, &L) == 2) {
		if(A < 0 && L < 0)
			break;
		int r = 1;
		TA = A;
		while(A != 1) {
			if(A&1)
				A = A*3+1;
			else
				A = A/2;
			if(A > L)
				break;
			r++;
		}
		printf("Case %d: A = %lld, limit = %lld, number of terms = %d\n", ++Case, TA, L, r);
	}
    return 0;
}
