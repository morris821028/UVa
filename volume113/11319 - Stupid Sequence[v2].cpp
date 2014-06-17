#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
using namespace std;
unsigned long long s[1505];
unsigned long long o[1505];
#define eps 1e-6
int main() {
    //freopen("in.txt", "r+t", stdin);
    int testcase;
    scanf("%d", &testcase);
    int i, j, k;
    while(testcase--) {
        for(i = 1; i <= 1500; i++) {
            scanf("%llu", &o[i]);
            s[i] = o[i];
        }
        long long sol[10];
        int hasSol = 1;
        for(i = 0; i <= 6; i++) {
            sol[i] = (s[1001]%1001+1001)%1001;
            if(s[1001] < sol[i])
                while(1);
            s[1001] = (s[1001] - sol[i])/1001;
        }
        for(i = 1; i <= 1500 && hasSol; i++) {
            unsigned long long sum = 0, tmp = 1;
            for(j = 0; j <= 6; j++)
                sum += sol[j] * tmp, tmp *= i;
            if(sum != o[i])
                hasSol = 0;
        }
        if(hasSol) {
            printf("%lld", sol[0]);
            for(i = 1; i <= 6; i++)
                printf(" %lld", sol[i]);
            puts("");
        } else
            puts("This is a smart sequence!");
    }
    return 0;
}
