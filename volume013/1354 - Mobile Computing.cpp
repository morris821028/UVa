#include <stdio.h>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
int N;
double R, x, ret;
#define eps 1e-8
struct Pos {
    double L, R, w;
    Pos(double a = 0, double b = 0, double c = 0):
    L(a), R(b), w(c) {}
};
Pos merge(Pos a, Pos b) {
    double la = b.w / (a.w + b.w), lb = a.w / (a.w + b.w);
    return Pos(max(la + a.L, -lb + b.L), max(lb + b.R, -la + a.R), a.w + b.w);
}
void dfs(vector<Pos> &state) {
    if (state.size() == 1) {
        if (state[0].L + state[0].R <= R + eps)
            ret = max(ret, state[0].L + state[0].R);
        return ;
    }
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.size(); j++) {
            if (i == j)
                continue;
            vector<Pos> nstate;
            for (int k = 0; k < state.size(); k++) {
                if (k == i || k == j)
                    continue;
                nstate.push_back(state[k]);
            }
            Pos a = state[i], b = state[j];
            Pos x = merge(a, b);
            if (x.L + x.R > R + eps)
                continue;
            nstate.push_back(x);
            dfs(nstate);
        }
    }
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%lf %d", &R, &N);
        vector<Pos> v;
        for (int i = 0; i < N; i++) {
            scanf("%lf", &x);
            v.push_back(Pos(0, 0, x));
        }
        ret = -1;
        dfs(v);
        if (ret < 0) {
            puts("-1");
        } else {
            printf("%.16lf\n", ret);
        }
    }
    return 0;
}
/*
 5
 1.3
 3
 1
 2
 1
 1.4
 3
 1
 2
 1
 2.0
 3
 1
 2
 1
 1.59
 4
 2
 1
 1
 3
 1.7143 
 4 
 1 
 2 
 3 
 5
*/