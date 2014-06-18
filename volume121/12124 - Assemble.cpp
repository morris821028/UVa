#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
int main() {
    int testcase, n, m;
    int i, j;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        map<string, vector<pair<int,int> > > R;
        map<string, vector<pair<int,int> > >::iterator it;
        vector<pair<int,int> >::iterator jt;
        char TYPE[105];
        int p, q;
        for(i = 0; i < n; i++) {
            scanf("%s %*s %d %d", TYPE, &p, &q);
            R[TYPE].push_back(make_pair(p, q));
        }
        int l, r, mid;//binary search quality
        int cost, onecost;
        int ret = 0;
        l = 0, r = 1000000000;
        while(l <= r) {
            mid = (l+r)/2;
            cost = 0;
            for(it = R.begin(); it != R.end(); it++) {
                onecost = 1000000000;
                for(jt = (it->second).begin(); jt != (it->second).end();
                    jt++) {
                    if(jt->second >= mid)
                        onecost = min(onecost, jt->first);
                }
                cost += onecost;
                if(cost > m)
                    break;
            }
            if(cost <= m)
                l = mid+1, ret = max(ret, mid);
            else
                r = mid-1;
        }
        printf("%d\n", ret);
    }
    return 0;
}
