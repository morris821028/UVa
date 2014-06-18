#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;
int main() {
    int m;
    string line;
    scanf("%d ", &m);
    while(m--) {
        getline(cin, line);
        stringstream sin(line);
        int n = 0, A[500], sum = 0;
        while(sin >> A[n])
            sum += A[n], n++;
        int dp[500] = {};
        dp[0] = 1;
        if(sum&1)
            puts("No");
        else {
            sum /= 2;
            int i, j;
            for(i = 0; i < n; i++) {
                for(j = sum; j >= A[i]; j--) {
                    if(dp[j-A[i]] != 0)
                        dp[j] = 1;
                }
            }
            if(dp[sum])
                puts("Yes");
            else
                puts("No");
        }
    }
    return 0;
}
