#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 1024;
int N, D, K;
vector< vector<int> > C;
struct Product {
    int v[8], id;
    bool operator<(const Product &a) const {
        return sum() > a.sum();
    }
    int sum() const {
        int s = 0;
        for (int i = 0; i < D; i++)
            s += v[i];
        return s;
    }
    int domain(Product &u) {
        for (auto &x : C) {
            int h1 = 1, h2 = 0;
            for (auto &e : x) {
                h1 &= v[e] >= u.v[e];
                h2 |= v[e] >  u.v[e];
            }
            if (h1 && h2)   return 1;
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
        for (int i = 0; i < (1<<D); i++) {
            if (__builtin_popcount(i) == K) {
                vector<int> A;
                for (int j = 0; j < D; j++) {
                    if ((i>>j)&1)
                        A.push_back(j);
                }
                C.push_back(A);
            }
        }
        
        vector<Product> filter;
        vector<int> ret;
        for (int i = 0; i < N; i++)
            used[i] = 0;
        for (int i = 0; i < N; i++) {
            if (used[i] == 0) {
                filter.push_back(item[i]);
                for (int j = i+1; j < N; j++) {
                    if (used[j] == 0 && item[i].domain(item[j]))
                        used[j] = 1;
                }
            }
        }
        for (int i = 0; i < filter.size(); i++) {
            int ok = 1;
            for (int j = 0; j < N && ok; j++) {
                if (item[j].domain(filter[i]))
                    ok = 0;
            }
            if (ok == 1)
                ret.push_back(filter[i].id);
        }
        
        sort(ret.begin(), ret.end());
        printf("Case #%d:", ++cases);
        for (int i = 0; i < ret.size(); i++)
            printf(" %d", ret[i]+1);
        puts(ret.size() ? "" : " NONE");
    }
    return 0;
}
