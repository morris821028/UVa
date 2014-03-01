#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
int main() {
    /*freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);*/
    double D, M, A, J;
    double d;
    while(scanf("%lf %lf %lf %lf", &D, &M, &A, &J) == 4) {
        d = D/2;
        double t1, t2, v3;
        double d1, d2, d3;
        double ret = 1e+60;
        double l = 0, r = M, m;
        m = M;
        t1 = A/J;
        if(2*t1*A/2 > m) {
            t1 = sqrt(m/J);
            t2 = t1;
        } else {
            t2 = (m-A*t1)/A+t1;
        }
        v3 = J*t1*t1/2 + J*t1*(t2-t1) + J*t1*t1/2;
        d1 = J*t1*t1*t1/6;
        d2 = (J*t1*t1 + J*t1*(t2-t1))*(t2-t1)/2;
        d3 = (J*t1*t1/2 + J*t1*(t2-t1))*t1 + J*t1*t1*t1/2 - J*t1*t1*t1/6;
        if(d1+d2+d3 > d) {
            t1 = pow(d/J, 1/3.0);
            t2 = t1;
            v3 = J*t1*t1/2 + J*t1*(t2-t1) + J*t1*t1/2;
            d1 = J*t1*t1*t1/6;
            d2 = (J*t1*t1 + J*t1*(t2-t1))*(t2-t1)/2;
            d3 = (J*t1*t1/2 + J*t1*(t2-t1))*t1 + J*t1*t1*t1/2 - J*t1*t1*t1/6;
            if(t1*J > A) {//d1+d2+d3 = d => at2^2 + bt2 + c = 0
                t1 = A/J;
                double a, b, c;
                a = J*t1/2, b = J*t1*t1/2, c = -d;
                t2 = ((-b)+sqrt(b*b-4*a*c))/(2*a);
                v3 = J*t1*t1/2 + J*t1*(t2-t1) + J*t1*t1/2;
                d1 = J*t1*t1*t1/6;
                d2 = (J*t1*t1 + J*t1*(t2-t1))*(t2-t1)/2;
                d3 = (J*t1*t1/2 + J*t1*(t2-t1))*t1 + J*t1*t1*t1/2 - J*t1*t1*t1/6;
                ret = min(ret, t1+t2+(d-d1-d2-d3)/v3);
            } else
                ret = min(ret, t1+t2+(d-d1-d2-d3)/v3);
        } else {
            ret = min(ret, t1+t2+(d-d1-d2-d3)/v3);
        }
        //printf("%lf %lf %lf %lf\n", t1, t2, d3, d1+d2+d3);

        printf("%.1lf\n", ret*2);
    }
    return 0;
}
/*
52 1 72 63
52.3
*/
