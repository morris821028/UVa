#include <stdio.h>
#include <map>
#include <set>
using namespace std;

int main() {
    int t, cases = 0;
    int n, x, y;
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        map<int, set<int> >g;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &y, &x);
            g[x].insert(y);
        }
        long long ans = 0, tmp;
        for(map<int, set<int> >::iterator it = g.begin();
            it != g.end(); it++) {
            map<int, set<int> >::iterator jt = it;
            for(jt++; jt != g.end(); jt++) {
                set<int>::iterator pt, qt;
                pt = it->second.begin();
                qt = jt->second.begin();
                tmp = 0;
                while(pt != it->second.end() && qt != jt->second.end()) {
                    if(*pt == *qt) {
                        tmp++;
                        pt++;
                        qt++;
                    }
                    else if(*pt < *qt)
                        pt++;
                    else
                        qt++;
                }
                ans += tmp*(tmp-1)/2;
            }
        }
        printf("Case %d: %lld\n", ++cases, ans);
    }
    return 0;
}
