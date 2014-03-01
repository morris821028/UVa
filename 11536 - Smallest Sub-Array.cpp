#include <stdio.h>
int X[1000005] = {0,1,2,3};
int main() {
    int T, cases = 0;
    int N, M, K, i;
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d %d", &N, &M, &K);
        int modM[3005] = {};
        for(i = 0; i < 3005; i++)
            modM[i] = i%M;
        for(i = 4; i <= N; i++) {
            X[i] = X[i-1] + X[i-2] + X[i-3];
            if(X[i] >= M)   X[i] = modM[X[i]];
            X[i] ++;
        }
        int used[105] = {}, d = 0;
        int tail = 1, mndist = 0xfffffff;
        for(i = 1; i <= N; i++) {
            while(tail <= N && d < K) {
                if(X[tail] <= K && used[X[tail]] == 0)
                    d++;
                if(X[tail] <= K)
                    used[X[tail]]++;
                tail++;
            }
            if(tail > N && d < K)
                break;
            if(mndist > tail-i && d == K)
                mndist = tail-i;
            if(X[i] <= K && used[X[i]] == 1)
                d--;
            if(X[i] <= K)
                used[X[i]]--;
        }
        printf("Case %d: ", ++cases);
        if(mndist != 0xfffffff)
            printf("%d\n", mndist);
        else
            puts("sequence nai");
    }
    return 0;
}
