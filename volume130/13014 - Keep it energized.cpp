#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
using namespace std;

const int MAXN = 131072;

int E[MAXN];
long long sumE[MAXN];
vector< pair<int, int> > shop[MAXN];
struct ELE {
    long long cost;
    int x, e;
    ELE(long long cost = 0, int x = 0, int e = 0):
    cost(cost), x(x), e(e) {}
    bool operator<(const ELE &v) const {
        if (cost != v.cost)
            return cost < v.cost;
        if (x != v.x)
            return x < v.x;
        return e < v.e;
    }
};
int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        for (int i = 1; i <= N; i++)
            scanf("%d", &E[i]), shop[i].clear();
        for (int i = 0; i < M; i++) {
            int L, S, C;
            scanf("%d %d %d", &L, &S, &C);
            shop[L].push_back(make_pair(S, C));
        }
        
        for (int i = 1; i <= N; i++)
            sumE[i] = sumE[i-1] + E[i];
        
        set<ELE> S;
        for (int i = 1; i <= N; i++) {
            while (!S.empty()) {
                ELE u = *S.begin();
                if (u.e < sumE[i-1] - sumE[u.x-1])
                    S.erase(S.begin());
                else
                    break;
            }
            if (S.empty() && i != 1) {
            } else {
                long long mm = i == 1 ? 0 : S.begin()->cost;
                for (int j = 0; j < shop[i].size(); j++) {
                    pair<int, int> p = shop[i][j];
                    if (p.first >= E[i])
                        S.insert(ELE(mm + p.second, i, p.first));
                }
            }
        }
        while (!S.empty()) {
            ELE u = *S.begin();
            if (u.e < sumE[N] - sumE[u.x-1])
                S.erase(S.begin());
            else
                break;
        }
        if (S.empty())
            puts("-1");
        else
            printf("%lld\n", S.begin()->cost);
    }
    return 0;
}