#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
const double PI = 3.141592653589793239, e = 2.7182818284590452354;
double dp[100005];
int DIGIT(int N, int B) {
    if(N > 100000) {
        int res = (int)((log(sqrt(2*PI*N)) + N*log(N/e))/log(B))+1;
        return res;
    }
    return ceil(dp[N]/log(B) + 1e-10);
}
int ZERO(int N, int B) {
    int i, zero = 0xfffffff, a, b, tmp;
    for(i = 2; i <= B; i++) {
        if(B%i == 0) {
            a = 0;
            while(B%i == 0)
                a++, B /= i;
            b = 0;
            tmp = N;
            while(tmp)
                b += tmp/i, tmp /= i;
            zero = min(zero, b/a);
        }
    }
    if(zero == 0xfffffff)
        return 0;
    return zero;
}
int main() {
    int N, B, i;
    for(i = 1; i < 100005; i++)
        dp[i] = dp[i-1]+log(i);
    while(scanf("%d %d", &N, &B) == 2) {
        printf("%d %d\n", ZERO(N, B), DIGIT(N, B));
    }
    return 0;
}
