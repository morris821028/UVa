#include<stdio.h>   
#include<math.h>   
main() {
	double a, b, c; 
	double cos, sin, S;
	while(scanf("%lf %lf %lf", &a, &b, &c) == 3) {  
    	if(a == 0 && b==0 && c == 0) break;
		cos = (a*a + b*b - c*c) /(double)a / (double)b / 2.0;
		sin = sqrt(1 - cos*cos);
		S = 0.5 * a * b * sin;
		printf("%.2lf\n",sqrt( (a*a + b*b + c*c)/2.0 + 2 * sqrt(3) * S ));
	}
	return 0;
}
