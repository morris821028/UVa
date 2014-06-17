#include<stdio.h>
main() {
	long long a, b, c;
	while(scanf("%lld", &a) == 1) {
		int Ans = 2147483647; 
		for(b = a+1; b <= 2*a; b++) {
			if((a*b+1)%(b-a) == 0) {
				c = (a*b+1)/(b-a); 
				if(b+c < Ans) Ans = b+c; 
			} 
		} 
		printf("%d\n", Ans); 
	}
	return 0; 
}
/*
1/a = (1/b + 1/c) /(1 - 1/bc) 
1/a = (b+c) / (bc-1) 
a = (bc-1) / (b+c)
a = b - (b*c-1)/(b+c) 
³] b >= c => 1<= c <=b , b > a 
b [a+1, 2*a] => 2a - (4a*a-1)/(4a) = 2a - a 
*/ 
