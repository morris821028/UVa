#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;
struct Pt {
    int x, y;
    Pt(int a, int b):
        x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(x != a.x)
            return x < a.x;
        return y < a.y;
    }
};
int main() {
    int testcase, cases = 0;
    int n, x, y;
    int i, j;
    scanf("%d", &testcase);
    while(testcase--) {
        printf("Case #%d:\n", ++cases);
        scanf("%d", &n);
        multiset<Pt> S;
        multiset<Pt>::iterator it;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            Pt p(x, y);
            it = S.lower_bound(p);
            if(it == S.begin() || (--it)->y > y) {
                S.insert(p);
                it = S.upper_bound(p);
                while(it != S.end() && it->y >= y)
                    S.erase(it++);
            }
            printf("%d\n", S.size());
        }
        if(testcase)
            puts("");
    }
    return 0;
}
