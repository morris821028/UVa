#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define eps 1e-7
struct Pt {
    int x, y;
    bool operator<(const Pt &p) const {
        if(x != p.x)
            return x > p.x;
        return y > p.y;
    }
};
int main() {
    char s[50];
    const double pi = acos(-1);
    int n, i, cases = 0;
    double a, b;
    while(scanf("%s %d", s, &n) == 2) {
        if(sscanf(s, "%lf+%lfi", &a, &b) == 2)
            {}
        else
            sscanf(s, "%lf-%lfi", &a, &b), b = -b;
        double theta = atan2(b, a);
        double k = pow(sqrt(a*a+b*b), 1.0/n);
        double px, py;
        int a, b, c, d;
        Pt D[n];
        for(i = 0; i < n; i++) {
            px = k*cos((theta+i*2*pi)/n);
            py = k*sin((theta+i*2*pi)/n);
            sprintf(s, "%.3lf%+.3lf", px, py);
            char op;
            sscanf(s, "%d.%d%c%d.%d", &a, &b, &op, &c, &d);
            if(c == 0 && d == 0)    op = '+';
            D[i].x = abs(a)*1000 + b;
            if(a < 0)   D[i].x = -D[i].x;
            D[i].y = abs(c)*1000 + d;
            if(op == '-')   D[i].y = -D[i].y;
        }
        sort(D, D+n);
        printf("Case %d:\n", ++cases);
        for(i = 0; i < n; i++) {
            if(D[i].x < 0)  putchar('-'), D[i].x = -D[i].x;
            printf("%d.%03d", D[i].x/1000, D[i].x%1000);
            if(D[i].y < 0)  putchar('-'), D[i].y = -D[i].y;
            else            putchar('+');
            printf("%d.%03di\n", D[i].y/1000, D[i].y%1000);

        }
        puts("");
    }
    return 0;
}
