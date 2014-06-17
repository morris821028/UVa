#include <stdio.h>
#include <map>
using namespace std;
long long x[10000], y[10000], avex, avey, n;
void solve() {
    if(avex%n || avey%n) {
        puts("no");
        return;
    }
    avex /= n, avey /= n;
    map<long long, int> r;
    int i;
    for(i = 0; i < n; i++)
        r[x[i]*100000000+y[i]] = 1;
    long long xx, yy;
    for(i = 0; i < n; i++) {
        xx = 2*avex - x[i];
        yy = 2*avey - y[i];
        if(r[x[i]*100000000+y[i]] == 0) {
            puts("no");
            return;
        }
    }
    puts("yes");
}
int main() {
    int t, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld", &n);
        avex = 0, avey = 0;
        for(i = 0; i < n; i++) {
            scanf("%lld %lld", &x[i], &y[i]);
            avex += x[i], avey += y[i];
        }
        solve();
    }
    return 0;
}
