#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 40005;
int N, D, K;
vector< vector<int> > C;
struct Product {
    int v[8], id;
    Product() {
    }
    bool operator<(const Product &a) const {
        return sum() > a.sum();
    }
    int sum() const {
        int s = 0;
        for (int i = 0; i < D; i++)
            s += v[i];
        return s;
    }
    int dist(Product &u) {
        int ret = 0;
        for (int i = 0; i < D; i++)
            ret += abs(v[i] - u.v[i]);
        return ret;
    }
    int domain(Product &u, int K) {
        vector<int> &C = Comb[K];
        for (int i = (int) C.size()-1; i >= 0; i--) {
            int h1 = 1, h2 = 0;
            for (int j = 0; j < D && h1; j++) {
                if ((C[i]>>j)&1) {
                    h1 &= v[j] >= u.v[j];
                    h2 |= v[j] >  u.v[j];
                }
            }
            if (h1 && h2)
                return 1;
        }
        return 0;
    }
} item[MAXN];
int used[MAXN];
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d %d", &N, &D, &K);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < D; j++)
                scanf("%d", &item[i].v[j]);
            item[i].id = i;
        }
        sort(item, item+N);
        
        C.clear();
        for (int i = 0; i <= D; i++)
            Comb[i].clear();
        for (int i = 0; i < (1<<D); i++) {
            int s = __builtin_popcount(i);
            Comb[s].push_back(i);
        }
        
        vector<Product> filter;
        vector<int> ret;
        for (int i = 0; i < N; i++)
            used[i] = 0;
        for (int i = 0; i < N; i++) {
            if (used[i] == 0) {
                filter.push_back(item[i]);
                for (int j = i+1; j < N; j++)
                    if (used[j] == 0 && item[i].domain(item[j], K))
                        used[j] = 1;
            }
        }
        for (int i = 0; i < filter.size(); i++) {
            int ok = 1;
            for (int j = 0; j < N && ok; j++) {
                if (item[j].domain(filter[i], K))
                    ok = 0;
            }
            if (ok == 1)
                ret.push_back(filter[i].id);
        }
        
        sort(ret.begin(), ret.end());
        printf("Case #%d:", ++cases);
        for (int i = 0; i < ret.size(); i++)
            printf(" %d", ret[i]+1);
        if (ret.size() == 0)
            puts(" NONE");
        else
            puts("");
    }
    return 0;
}
/*
 4
 
 2 3 1
 20 20 20
 20 20 20
 
 2 5 1
 20 5 20 20 20
 5 20 20 20 20
 
 4 6 5
 9 4 9 7 7 9
 9 7 9 6 5 4
 9 6 9 8 3 3
 1 2 3 9 2 2
 
 8 6 5
 3 3 5 6 6 8
 9 4 9 7 7 9
 8 4 7 9 2 7
 5 6 8 9 5 9
 9 7 9 6 2 4
 6 6 6 5 3 5
 5 7 3 8 4 6
 4 4 8 6 6 4
 */
