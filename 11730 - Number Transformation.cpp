#include <stdio.h>
#include <queue>
using namespace std;
int p[1005], pt;
void sieve() {
    int mark[1005] = {}, i, j;
    pt = 0;
    for(i = 2; i < 1000; i++) {
        if(mark[i] == 0) {
            for(j = i+i; j < 1000; j += i)
                mark[j] = 1;
            p[pt++] = i;
        }
    }
}
int main() {
    sieve();
    int A, B, i, cases = 0;
    while(scanf("%d %d", &A, &B) == 2) {
        if(A == 0)  break;
        queue<int> Q;
        int dp[1005] = {}, used[1005] = {};
        Q.push(A);
        used[A] = 1;
        while(!Q.empty() && !used[B]) {
            A = Q.front(), Q.pop();
            for(i = 0; i < pt && p[i] < A; i++) {
                if(used[A+p[i]] == 0 && A%p[i] == 0) {
                    if(A+p[i] <= B) {
                        dp[A+p[i]] = dp[A]+1, used[A+p[i]] = 1;
                        Q.push(A+p[i]);
                    }
                }
            }
        }
        printf("Case %d: ", ++cases);
        if(used[B]) printf("%d\n", dp[B]);
        else    puts("-1");
    }
    return 0;
}
