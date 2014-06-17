#include<stdio.h>
int main() {
	long long int k;
	while(scanf("%lld", &k) == 1 && k >= 0) {
		printf("%lld\n", k*(k+1)/2+1);
	}
    return 0;
}
