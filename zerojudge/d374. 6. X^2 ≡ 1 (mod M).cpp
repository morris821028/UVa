#include <stdio.h>
#include <math.h>
#include <set>
using namespace std;
int gcd(int a, int b) {
    int t;
    while(a%b)
        t = a, a = b, b = t%b;
    return b;
}
void gcd_(int a, int b, int &s, int &t) {
    int s_ = 1, t_ = 0;
    int flag = 1, tmp;
    s = 0, t = 1;
    while(a%b) {
        if(!flag) {
            s -= a/b * s_;
            t -= a/b * t_;
        } else {
            s_ -= a/b * s;
            t_ -= a/b * t;
        }
        tmp = a, a = b, b = tmp%b;
        flag = 1-flag;
    }
    if(!flag)    s = s_, t = t_;
}
set<int> QQ;
void sol(int Mp, int Mq) {
    int g = gcd(Mp, Mq), c = 2;
    if(c%g == 0) {
        int s, t;
        gcd_(Mp, -Mq, s, t);
        int x1 = s*(c/g);
        int y1 = t*(c/g);
        printf("%d %d %d %d\n", Mp, Mq, s, t);
        while(x1 >= 0 && y1 >= 0) {
            if((Mp*x1 + Mq*y1)%2 == 0) {
                printf("%d ->\n", (Mp*x1 + Mq*y1)/2);
                QQ.insert((Mp*x1 + Mq*y1)/2);
                QQ.insert(Mp*Mq - (Mp*x1 + Mq*y1)/2);
            }
            x1 = x1 + Mq/g;
            y1 = y1 - Mp/g;
        }
    }
}
int main() {
    int M, i;
    while(scanf("%d", &M) == 1) {
        int sq = (int)sqrt(M);
        QQ.clear();
        for(i = 1; i <= sq; i++) {
            if(M%i == 0) {
                int Mp = M/i, Mq = i;
                sol(Mp, Mq);
                sol(Mq, Mp);
            }
        }
        printf("%d\n", QQ.size());
        for(set<int>::iterator it = QQ.begin(); it != QQ.end(); it++)
            printf("%d\n", *it);
    }
    return 0;
}
