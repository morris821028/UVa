#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
struct E {
    int s, a, b, c;
    E(int x, int y, int z, int w):
        s(x), a(y), b(z), c(w) {}
    bool operator<(const E &A) const {
        if(s != A.s)
            return s < A.s;
        return a < A.a;
    }
};
int main() {
    int a, b, c, d;
    int n, m;
    int cnt = 0;
    vector<E> A;
    for(a = 1; a+a+a <= 25600; a++) {
        for(b = a; a+b+b <= 25600; b++) {
            long long p = (long long)a*b;
            long long s = a+b;
            if(p <= 10000)  continue;
            c = (s * 10000LL) / (p - 10000);
            s += c;
            if(s > 25600 || c < b)  continue;
            if(a + b + c == (long long)a*b*c/10000) {
                A.push_back(E(s, a, b, c));
            }
        }
    }
    sort(A.begin(), A.end());
    while(scanf("%d.%d %d.%d", &a, &b, &c, &d) == 4) {
        n = a*100+b;
        m = c*100+d;
        int i, j, k;
        for(i = 0; i < A.size(); i++) {
            if(A[i].s >= n && A[i].s <= m) {
                a = A[i].a, b = A[i].b, c = A[i].c;
                printf("%d.%02d = ", A[i].s/100, A[i].s%100);
                printf("%d.%.02d + %d.%02d + %d.%02d = ", a/100, a%100, b/100, b%100, c/100, c%100);
                printf("%d.%.02d * %d.%02d * %d.%02d\n", a/100, a%100, b/100, b%100, c/100, c%100);
            }
        }
    }
    return 0;
}
