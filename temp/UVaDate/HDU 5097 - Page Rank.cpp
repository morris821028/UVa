#include <stdio.h>
#include <math.h>
#include <vector>
#include <string.h>
using namespace std;
// Markov process, math
const int MAXN = 4096;
const int MAXIT = 9999;
class PageRank {
public:
    const double eps = 1e-10;
    vector<int> g[MAXN], invg[MAXN];
    vector<double> r;
    int N;
    double beta, S;
    void init(int n, double beta) {
        this->N = n;
        this->beta = beta;
        for (int i = 0; i < n; i++)
            g[i].clear(), invg[i].clear();
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        invg[v].push_back(u);
    }
    bool isComplete(vector<double> &a, vector<double> &b) {
        double e = 0;
        for (int i = (int) a.size() - 1; i >= 0; i--) {
            e += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return e < eps;
    }
    void compute() {
        vector<double> next_r(N, 0);
        r.resize(N, 1.0);
        
        for (int it = 0; it < MAXIT; it++) {
            for (int i = 0; i < N; i++) {
                double tmp = 0;
                for (int j = 0; j < invg[i].size(); j++) {
                    int x = invg[i][j];
                    tmp += r[x] / g[x].size();
                }
                next_r[i] = tmp * beta + (1.0 - beta);
            }
            if (isComplete(r, next_r)) {
                r = next_r;
                return ;
            }
            r = next_r;
        }
    }
} g;

char s[MAXN][MAXN];
int main() {
    const double beta = 0.85f;
    int N;
    while (scanf("%d", &N) == 1) {
        for (int i = 0; i < N; i++)
            scanf("%s", s[i]);
        
        g.init(N, beta);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (s[i][j] == '1') {
                    g.addEdge(i, j);
                }
            }
        }
        
        g.compute();
        
        for (int i = 0; i < N; i++) {
            printf("%.2lf%c", g.r[i], i == N - 1 ? '\n' : ' ');
        }
    }
    return 0;
}