#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#define MAXN 16
#define MAXM 105
#define MAXSTATE 524288
#define INF (1LL<<60)
#define eps 1e-3
using namespace std;
int si[MAXN], ki[MAXN];
double stockTable[MAXN][MAXM], C;
int M, N, K;
char stockName[MAXN][MAXN];
int ReadFloat(int &C) {
    char s[1024];
    if (scanf("%s", s) == 1) {
        int x = 0, n = (int) strlen(s), b = 2;
        for (int i = 0; i < n; i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                x = x * 10 + s[i] - '0';
            } else {
                for (i++; i < n; i++) {
                    x = x * 10 + s[i] - '0';
                    b--;
                }
                break;
            }
        }
        while (b--)
            x = x * 10;
        C = x;
        return 1;
    } else
        return 0;
}

vector< vector<int> > states;
map< vector<int>, int> stateId;
int gbuy[MAXSTATE][MAXN], gsell[MAXSTATE][MAXN];
double dp[MAXM][MAXSTATE];
pair<int, int> from[MAXM][MAXSTATE];
void dfs(int idx, vector<int>&state, int sum) {
    if (idx == N) {
        int id = (int) stateId.size();
        stateId[state] = id;
        states.push_back(state);
        return ;
    }
    for (int i = 0; i <= ki[idx] && sum + i <= K; i++) {
        state[idx] = i;
        dfs(idx+1, state, sum + i);
    }
}
void buildDAG() {
    vector<int> st(N, 0);
    states.clear();
    stateId.clear();
    dfs(0, st, 0);
    assert(states.size() < MAXSTATE);
    for (int i = 0; i < states.size(); i++) {
        int sum = 0;
        vector<int> &u = states[i];
        for (int j = 0; j < N; j++)
            sum += u[j];
        for (int j = 0; j < N; j++) {
            gbuy[i][j] = gsell[i][j] = -1;
            if (u[j] < ki[j] && sum < K) {
                vector<int> v = u;
                v[j]++;
                gbuy[i][j] = stateId[v];
            }
            if (u[j] > 0) {
                vector<int> v = u;
                v[j]--;
                gsell[i][j] = stateId[v];
            }
        }
    }
}
void update(int day, int u, int v, double val, int data) {
    if (val > dp[day+1][v]) {
        dp[day+1][v] = val;
        from[day+1][v] = make_pair(u, data);
    }
}
int main() {
    int cases = 0;
    while (scanf("%lf", &C) == 1) {
        scanf("%d %d %d", &M, &N, &K);
        for (int i = 0; i < N; i++) {
            scanf("%s %d %d", stockName[i], &si[i], &ki[i]);
            for (int j = 0; j < M; j++) {
                scanf("%lf", &stockTable[i][j]);
                stockTable[i][j] *= si[i];
            }
        }
        buildDAG();
        
        for (int i = 0; i <= M; i++)
            for (int j = 0; j < states.size(); j++)
                dp[i][j] = -INF;
        dp[0][0] = C;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < states.size(); j++) {
                double val = dp[i][j];
                if (val < 0)  continue;
                update(i, j, j, val, 0);
                for (int k = 0; k < N; k++) {
                    if (gbuy[j][k] >= 0 && val >= stockTable[k][i] - eps) {
                        update(i, j, gbuy[j][k], val - stockTable[k][i], k+1);
                    }
                    if (gsell[j][k] >= 0) {
                        update(i, j, gsell[j][k], val + stockTable[k][i], -(k+1));
                    }
                }
            }
        }
        
        if (cases++)    puts("");
        printf("%.2lf\n", dp[M][0]);
        vector<int> ret;
        for (int i = M, j = 0; i > 0; i--) {
            ret.push_back(from[i][j].second);
            j = from[i][j].first;
        }
        for (int i = (int) ret.size() - 1; i >= 0; i--) {
            if (ret[i] > 0) {
                printf("BUY %s\n", stockName[ret[i]-1]);
            } else if (ret[i] < 0) {
                printf("SELL %s\n", stockName[-ret[i]-1]);
            } else {
                puts("HOLD");
            }
        }
    }
    return 0;
}
/*
 
*/