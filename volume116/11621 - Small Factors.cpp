#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    long long n, res, i, j;
    vector<long long> buf;
    for(i = 0; i < 32; i++) {
        for(j = 0; j < 32; j++) {
            double p = pow(2,i)*pow(3,j);
            if(p <= 1LL<<50) {
                buf.push_back(p);
            }
        }
    }
    sort(buf.begin(), buf.end());
    while(scanf("%lld", &n) == 1 && n) {
        printf("%lld\n", *lower_bound(buf.begin(), buf.end(), n));
    }
    return 0;
}
