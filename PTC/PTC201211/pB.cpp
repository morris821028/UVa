#include <stdio.h>
#include <algorithm>
using namespace std;
struct ele {
    int idx, h;
};
ele A[100000];
bool cmp(ele a, ele b) {
    return a.h > b.h;
}
int main() {
    int N, Jf, Jc, Je;
    int F, C, E, H;
    int i;
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &N);
        scanf("%d %d %d", &Jf, &Jc, &Je);
        for(i = 0; i < N; i++) {
            scanf("%d %d %d %d", &F, &C, &E, &H);
            if(F > C && F > E) {
                A[i].idx = 0, A[i].h = H;
            } else if(C > F && C > E)
                A[i].idx = 1, A[i].h = H;
            else A[i].idx = 2, A[i].h = H;
        }
        sort(A, A+N, cmp);
        long long ans = 0;
        for(i = 0; i < N; i++) {
            if(A[i].idx == 0) {
                if(Jf > 0)
                    Jf--, ans += A[i].h;
            }
            if(A[i].idx == 1) {
                if(Jc > 0)
                    Jc--, ans += A[i].h;
            }
            if(A[i].idx == 2) {
                if(Je > 0)
                    Je--, ans += A[i].h;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
