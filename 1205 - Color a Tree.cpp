#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;

int main() {
    int N, R;
    int W[1024], father[1024], exists[1024], time[1024], cost[1024];
    int x, y;
    while (scanf("%d %d", &N, &R), N + R) {
        for (int i = 1; i <= N; i++) {
            scanf("%d", &W[i]);
        }
        for (int i = 1; i < N; i++) {
            scanf("%d %d", &x, &y);
            father[y] = x;
        }
        
        for (int i = 1; i <= N; i++) {
            exists[i] = 1;
            time[i] = 1;
            cost[i] = W[i];
        }
        
        for (int i = 1; i < N; i++) {
            int maxW = -1, maxX = 1;
            double maxP = -1;
            for (int j = 1; j <= N; j++) {
                if (exists[j] && maxP < (double)W[j]/time[j] && j != R) {
                    maxW = W[j], maxX = j;
                    maxP = (double)W[j]/time[j];
                }
            }
            for (int j = 1; j <= N; j++) {
                if (father[j] == maxX) {
                    father[j] = father[maxX];
                }
            }
            W[father[maxX]] += W[maxX];
            cost[father[maxX]] += time[father[maxX]] * W[maxX] + cost[maxX];
            time[father[maxX]] += time[maxX];
            exists[maxX] = 0;
            // printf("merge %d to %d. W = %d, cost = %d\n", maxX, father[maxX], maxW, cost[father[maxX]]);
        }
        int ret = cost[R];
        printf("%d\n", ret);
    }
    return 0;
}
/*
 5 1
 1 2 1 2 4
 1 2
 1 3
 2 4
 3 5
 0 0
*/
