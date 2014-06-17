#include <stdio.h>
#include <set>
using namespace std;

int main() {
    int n, m, x, i, tmp;
    while(scanf("%d", &n) == 1 && n) {
        multiset<int> S;
        multiset<int>::iterator it, jt, kt;

        long long sum = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &m);
            while(m--) {
                scanf("%d", &x);
                S.insert(x);
            }
            it = S.begin(), jt = S.end();
            jt--, sum += *jt - *it;
            S.erase(it);
            S.erase(jt);
            m = 2*(n-i+1);
            if(S.size() > m) {
                tmp = n-i+1;
                while(tmp)  it++, tmp--;
                tmp = n-i+1, kt = S.end();
                while(tmp)  kt--, tmp--;
                S.erase(it, kt);
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}
