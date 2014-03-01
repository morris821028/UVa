#include <stdio.h>
#include <math.h>
int gcd(int a, int b) {
    int t;
    while(a%b)
        t = a, a = b, b = b%t;
    return b;
}
void gcd_(int a, int b, int &s, int &t) {
    int s_ = 1, t_ = 0;
    int flag = 1;
    s = 0, t = 1;
    while(a%b) {
        if(flag&1) {
            s -= b/a * s_;
            t -= b/a * t_;
        } else {
            s_ -= b/a * s;
            t_ -= b/a * t;
        }
        t = a, a = b, b = b%t;
        flag = 1-flag;
    }
    if(flag)    s = _s, t = _t;
}
int main() {
    int M, i;
    while(scanf("%d", &M) == 1) {
        int sq = (int)sqrt(M);
        for(i = 1; i <= sq; i++) {
            if(M%i == 0) {
                int Mp = i, Mq = M/i;
                int g = gcd(Mp, Mq);
                if(2%g == 0) {
                    int s, t;
                    gcd_(Mp, Mq, s, t);
                    int x1 = s*(2/g);
                    int y1 = t*(2/g);
                    printf("%d %d\n", x1, y1);
                }
            }
        }
    }
    return 0;
}
