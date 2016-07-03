#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
#include <map>
#include <vector>
using namespace std;

const int MAXN = 16;
int dist[1<<MAXN][2], isValid[1<<MAXN];

int main() {
    int N, W, K;
    int A[MAXN];
    while (scanf("%d %d %d", &N, &W, &K) == 3) {
        for (int i = 0; i < N; i++)
            scanf("%d", &A[i]);
        
        sort(A, A+N);
        
        int M = (1<<N)-1;
        for (int i = 0; i <= M; i++) {
            dist[i][0] = dist[i][1] = 0x3f3f3f3f;
            isValid[i] = 0;
            if (__builtin_popcount(i) <= K) {
                int s = 0;
                for (int j = 0; j < N; j++) {
                    if ((i>>j)&1)
                        s += A[j];
                }
                if (s <= W)
                    isValid[i] = 1;
            }
        }
        queue<int> Q, L;
        Q.push((1<<N)-1), L.push(0);
        dist[(1<<N)-1][0] = 0;
        while (!Q.empty()) {
            int l = Q.front(), r = ((1<<N)-1)^Q.front();
            int p = L.front();
            Q.pop(), L.pop();
            if (p == 0)
            for (int i = l; i; i = (i-1)&l) {
                if (dist[l^i][!p] > dist[l][p] + 1 && isValid[i]) {
                    dist[l^i][!p] = dist[l][p] + 1;
                    Q.push(l^i), L.push(!p);
                }
            }
            if (p == 1)
            for (int i = r; i; i = (i-1)&r) {
                if (dist[l|i][!p] > dist[l][p] + 1 && isValid[i]) {
                    dist[l|i][!p] = dist[l][p] + 1;
                    Q.push(l|i), L.push(!p);
                }
            }
        }
        if (dist[0][1] == 0x3f3f3f3f)
            printf("-1\n");
        else
            printf("%d\n", dist[0][1]);
    }
    return 0;
}
/*
 3 100 2
 10 10 100
 4 100 2
 10 10 100 100
 1 100 1
 20
 1 100 3
 100
 2 100 2
 50 50
 3 50 2
 10 40 40
 2 100 3
 50 50
 2 100 2
 100 100
 2 100 1
 20 20
 5 15 5
 1 2 3 4 5
 5 15 3
 1 2 3 4 5
*/