#include <stdio.h>
#include <math.h>
int main() {
    int t;
    double pi = acos(-1);
    scanf("%d", &t);
    while(t--) {
        double B, H, C = 0;
        scanf("%lf %lf", &B, &H);
        double area = B*H/2;
        double L = sqrt(H*H + B*B/4)*2 + B;
        double R = area*2 / L;
        while(R >= 0.000001) {
            C += 2*pi*R;
            double tmp = H;
            H -= 2*R;
            R *= H/tmp;
        }
        printf("%13.6lf\n", C);
        if(t)
            puts("");
    }
    return 0;
}
