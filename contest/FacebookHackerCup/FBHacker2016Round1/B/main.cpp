#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 131072;
const int LMAX = 0x3f3f3f3f;

int main() {
    int testcase;
    int cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        int L, N, M, D, W, target;
        multiset< pair<long long, int> > EMPTYN;
        multiset<long long> EMPTYM;
        set<long long> timeline;
        multiset< pair<long long, int> > S;
        scanf("%d %d %d %d", &L, &N, &M, &D);
        for (int i = 0; i < N; i++) {
            scanf("%d", &W);
            EMPTYN.insert({W, W});
            timeline.insert(W);
        }
        
        target = L;
        int basket = 0;
        int complete = 0;
        long long ret = 0;
        timeline.insert(0);
        while (timeline.size() != 0) {
            long long time = *timeline.begin();
            timeline.erase(timeline.begin());
            while (L != 0 && EMPTYN.begin()->first <= time) {
                pair<long long, int> e = *EMPTYN.begin();
                EMPTYN.erase(EMPTYN.begin());
                EMPTYN.insert({e.first+e.second, e.second});
                timeline.insert(e.first+e.second);
                L--, basket++;
            }
            while (!EMPTYM.empty() && *EMPTYM.begin() <= time) {
                EMPTYM.erase(EMPTYM.begin());
                M++;
                complete++;
                if (complete == target)
                    ret = time;
            }
            while (basket > 0 && M > 0) {
                basket--, M--;
                EMPTYM.insert(time + D);
                timeline.insert(time + D);
            }
        }
        printf("Case #%d: %lld\n", ++cases, ret);
    }
    return 0;
}