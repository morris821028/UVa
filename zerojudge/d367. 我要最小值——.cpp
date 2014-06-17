#include<stdio.h>   
#include<math.h>   
#define magnify 1
double mysqrt(double x, int pre) {
	int i;
	double ten;
	double ans = 0;
	for(i = 0; i < pre; i++) {
		ten = pow(10, -i);
		while(ans*ans < x) ans += ten;
		ans -= ten;
	}
	return ans;
}
main() {
	long long a, b, c; 
	double A, s;
	while(scanf("%lld %lld %lld", &a, &b, &c) == 3) {  
    	if(a == 0 && b==0 && c == 0) break;
    	a *= magnify, b *= magnify, c *= magnify;
    	s = (a + b + c) / 2.0;
		A = mysqrt( s * (s-a) * (s-b) * (s-c) , 10);
		printf("%.2lf\n", mysqrt( (a*a + b*b + c*c)/2.0 + A * 2 * sqrt(3), 10)/ magnify);
	}
	return 0;      
}
/*
3 6 10
*/
