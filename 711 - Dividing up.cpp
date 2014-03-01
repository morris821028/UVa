#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int A[7], i;
    int cases = 0;
    while(1) {
        int sum = 0;
        for(i = 1; i <= 6; i++)
            scanf("%d", &A[i]), sum += i*A[i];
        if(sum == 0)
            break;
        printf("Collection #%d:\n", ++cases);
        if(sum%2) {
            puts("Can't be divided.\n");
            continue;
        }
        int hsum = sum/2, n, a, b, c;
        char m1[120005] = {}, m2[120005] = {};
        for(i = 0; i <= hsum; i++) { // 1 2 4
            n = i;
            a = A[1], b = A[2], c = A[4];
            if(n/4 >= c) n -= 4*c;
            else        n %= 4;
            if(n/2 >= b) n -= 2*b;
            else        n %= 2;
            if(n/1 >= a) n -= 1*a;
            else        n %= 1;
            if(n == 0)  m1[i] = 1;
        }
        if(A[3]) {
            a = A[3]*3+A[6]*6;
            for(i = 0; i <= a; i += 3)
                m2[i] = 1;
        } else {
            a = A[6]*6;
            for(i = 0; i <= a; i += 6)
                m2[i] = 1;
        }
        if(A[5]) {
            b = A[5];
            for(i = hsum; i >= 0; i--) {// (3 6) 5
                if(m2[i])   continue;
                n = i;
                b = 0;
                for(a = 0, b = min(A[5]*5, i/5*5); a <= b && !m2[i]; a += 5, b -= 5) {
                    if(m2[i-a] || m2[i-b])
                        m2[i] = 1;
                }
            }
        }
        for(i = 0; i <= hsum; i++) {
            if(m1[i] && m2[hsum-i])
                break;
        }
        if(i == hsum+1)
            puts("Can't be divided.");
        else
            puts("Can be divided.");
        puts("");
    }
    return 0;
}
