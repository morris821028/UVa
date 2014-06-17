#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
int main() {
    freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);
    double D, M, A, J;
    double d;
    while(scanf("%lf %lf %lf %lf", &D, &M, &A, &J) == 4) {
        d = D/2;
        double t1, t2 = 0, v3;
        double d1, d2, d3;
        double ret = 1e+60;
        double l, r;
#define eps 0
        for(t1 = eps; t1+t1 < ret; t1 += 0.3e-4) {
            if(J*t1 > A+eps)    break;
            l = t1, r = 1000;
            int cnt = 0;
            while(l <= r && cnt < 30) {
                t2 = (l+r)/2;
                v3 = J*t1*t1/2 + J*t1*(t2-t1) + J*t1*t1/2;
                d1 = J*t1*t1*t1/6.0;
                d2 = (J*t1*t1 + J*t1*(t2-t1))*(t2-t1)/2;
                d3 = (J*t1*t1/2 + J*t1*(t2-t1))*t1 + J*t1*t1*t1/2 - J*t1*t1*t1/6;
                if(d1+d2+d3 > d+eps || v3 > M+eps)
                    r = t2;
                else
                    l = t2;
                cnt++;
            }
            if(v3 < M+eps && d-d1-d2-d3 > -eps)
            ret = min(ret, t1+t2+(d-d1-d2-d3)/v3);
        }
        printf("%lf\n", ret*2);
    }
    return 0;
}
/*
52 1 72 63
52.3
*/
