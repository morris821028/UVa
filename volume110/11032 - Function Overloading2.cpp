#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
int dp1[10001000] = {};
char dp0[10001000] = {};
int main() {
    int k1, k2, k3, k4, k5, k6, k7, num, num2;
    for(k1 = 0; k1 < 10; k1++)
    for(k2 = 0; k2 < 10; k2++)
    for(k3 = 0; k3 < 10; k3++)
    for(k4 = 0; k4 < 10; k4++)
    for(k5 = 0; k5 < 10; k5++)
    for(k6 = 0; k6 < 10; k6++)
    for(k7 = 0; k7 < 10; k7++) {
        num = k7+k6*10+k5*100+k4*1000+k3*10000+k2*100000+k1*1000000;
        num2 = num+k1+k2+k3+k4+k5+k6+k7;
        //printf("%d\n", num);
        if(dp0[num2] == 0)    dp0[num2] = num2-num;
        if(num)
            dp1[num] = dp1[num-1] + (dp0[num] == 0);
    }
    dp1[10000000] = dp1[9999999] + (dp0[10000000] == 0);
    int t, cases = 0;
    char cmd[500];
    scanf("%d", &t);
    cin.ignore(100, '\n');
    while(t--) {
        gets(cmd);
        int a, b;
        printf("Case %d: ", ++cases);
        if(sscanf(cmd, "%d %d", &a, &b) == 2) {
            if(a > b)   puts("0");
            else
                printf("%d\n", dp1[b]-dp1[a-1]);
        } else {
            sscanf(cmd, "%d", &a);
            printf("%d\n", dp0[a] ? a-dp0[a] : -1);
        }
    }
    return 0;
}
