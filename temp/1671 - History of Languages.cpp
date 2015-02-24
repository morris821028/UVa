#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <list>
using namespace std;
#define MAXN 2048
#define MAXT 32
struct DFA {
public:
    int N, T, st;
    int trans[MAXN][MAXT], ac[MAXN];
    void init(int N, int T) {
        this->N = N;
        this->T = T;
        st = 0;
    }
    void read() {
        for (int i = 0; i < N; i++) {
            scanf("%d", &ac[i]);
            for (int j = 0; j < T; j++) {
                scanf("%d", &trans[i][j]);
            }
        }
    }
} A, B;
int visited[MAXN][MAXN];
int noIntersection(DFA &u, DFA &v) { // u' and v != empty
    static int cases = 0;
    ++cases;
    queue<int> P, Q;
    int p, q, x, y;
    P.push(u.st), Q.push(v.st), visited[u.st][v.st] = cases;
    while (!Q.empty()) {
        p = P.front(), P.pop();
        q = Q.front(), Q.pop();
        if (!u.ac[p] && v.ac[q])
            return 0;
        for (int i = 0; i < u.T; i++) {
            x = u.trans[p][i];
            y = v.trans[q][i];
            if (x == -1 && y != -1 && v.ac[y])
                return 0;
            if (x == -1 || y == -1 || visited[x][y] == cases)
                continue;
            visited[x][y] = cases;
            P.push(x), Q.push(y);
        }
    }
    cases++;
    return 1;
}
int main() {
    int T, N;
    int cases = 0;
    while (scanf("%d", &T) == 1 && T) {
        scanf("%d", &N);
        A.init(N, T);
        A.read();
        scanf("%d", &N);
        B.init(N, T);
        B.read();
        
        int f = noIntersection(A, B) && noIntersection(B, A);
        printf("Case #%d: %s\n", ++cases, f ? "Yes" : "No");
    }
    return 0;
}
/*
 
 */
