#include <bits/stdc++.h>
using namespace std;
int main() {
	const double pi = acos(-1);
    double a, b, c;
    while (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
        if (!a && !b && !c) break;
        if (a > b)	swap(a, b);
        if (b > c)	swap(b, c);
        double v = sqrt(-3*(pow(a,4)+pow(b,4)+pow(c,4))+6*a*a*b*b+6*b*b*c*c+6*c*c*a*a);
        double ret = sqrt((a*a+b*b+c*c+v)/2);
        double theta = acos((a*a+b*b-c*c)/2.0/a/b);
        if (theta >= pi*2/3)
        	printf("%.2lf\n", a+b);
        else
        	printf("%.2lf\n", (double) ret);
    }
    return 0;
}

