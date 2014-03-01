#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
int check(long long n, int flag) {
    if(n == 0) {
        printf("0 0\n");
        return 1;
    }
    int neg = 0;
    long long i, sq;
    long long a, b, c, d;
    if(n < 0)   neg = 1, n = -n;
    sq = (long long)sqrt(n);
    for(i = sq; i >= 1; i--) {
        if(n%i == 0) {
            c = i; //a-b
            d = n/i;//a+b
            if((c+d)%2 == 0 && (c-d)%2 == 0) {
                a = (c+d)/2;
                b = (d-c)/2;
                if(a >= 0 && b >= 0) {
                    if(flag) {
                        if(neg)
                            printf("%lld %lld\n", b, a);
                        else
                            printf("%lld %lld\n", a, b);
                    }
                    return 1;
                }
            }
        }
    }
    if(flag) {
        if(n%2)
            puts("Spinster Number.");
        else
            puts("Bachelor Number.");
    }
    return 0;
}
int cntBachelor(long long n1) {
    if(n1 < 0)  n1 = -n1;
    if(n1 < 2)  return 0;
    return (n1-2)/4+1;
}
int main() {
    char cmd[50];
    long long n1, n2;
    while(gets(cmd)) {
        if(sscanf(cmd,"%lld %lld", &n1, &n2) == 2) {
            long long i, j, t1, t2;
            if(n1 > n2) swap(n1, n2);
            if(n1 < 0 && n2 > 0) {
                t1 = cntBachelor(n1);
                t2 = cntBachelor(n2);
                j = t1+t2;
            } else {
                if(n1 < 0)  n1 = -n1, n2 = -n2;
                t1 = cntBachelor(abs(n1)-1);
                t2 = cntBachelor(n2);
                j = t2-t1;
            }
            printf("%lld\n", j);
        } else {
            sscanf(cmd, "%lld", &n1);
            check(n1, 1);
        }
    }
    return 0;
}
