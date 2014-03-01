#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Pt {
    long long x, y;
    Pt(long long a, long long b):
        x(a), y(b) {}
    Pt():
        x(0), y(0) {}
    Pt operator-(const Pt &a) {
        return Pt(x-a.x, y-a.y);
    }
};
Pt D[100000];
#define eps 1e-10
long long dist(Pt &a, Pt &b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
int main() {
    freopen("in2.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);
    int n, i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            scanf("%lld %lld", &D[i].x, &D[i].y);
            D[i+n] = D[i];
        }
        int lr = 1, ll = 1, rl = n-1, rr = n-1;
        for(i = 0; i < n; i++) {
            long long mxdist = 0;
            bool update;
            int L = i+1, R = n+i-1;
            if(ll < L)  ll = L, lr = ll;
            if(lr > R)  lr = R, ll = lr;
            do {
                update = false;
                while(ll-1 >= L) {
                    if(dist(D[i], D[ll-1]) == dist(D[i], D[ll]))
                        ll--, update = true;
                    else if(dist(D[i], D[ll-1]) > dist(D[i], D[ll]))
                        ll--, lr = ll, update = true;
                    else    break;
                }
                while(lr+1 <= R) {
                    if(dist(D[i], D[lr+1]) == dist(D[i], D[lr]))
                        lr++, update = true;
                    else if(dist(D[i], D[lr+1]) > dist(D[i], D[lr]))
                        lr++, ll = lr, update = true;
                    else    break;
                }
            } while(update);
            L = i+1, R = n+i-1;
            if(rr > R)  rr = R, rl = rr;
            if(rl < L)  rl = L, rr = rl;
            do {
                update = false;
                while(rr+1 <= R) {
                    if(dist(D[i], D[rr+1]) == dist(D[i], D[rr]))
                        rr++, update = true;
                    else if(dist(D[i], D[rr+1]) > dist(D[i], D[rr]))
                        rr++, rl = rr, update = true;
                    else    break;
                }
                while(rl-1 >= L) {
                    if(dist(D[i], D[rl-1]) == dist(D[i], D[rl]))
                        rl--, update = true;
                    else if(dist(D[i], D[rl-1]) > dist(D[i], D[rl]))
                        rl--, rr = rl, update = true;
                    else    break;
                }
            } while(update);
            int mnidx1, mnidx2;
            if(ll < n && lr >= n)
                mnidx1 = 0;
            else
                mnidx1 = ll%n;
            if(rl < n && rr >= n)
                mnidx2 = 0;
            else
                mnidx2 = rl%n;
            if(dist(D[i], D[mnidx2]) > dist(D[i], D[mnidx1]) ||
               (dist(D[i], D[mnidx2]) == dist(D[i], D[mnidx1]) && mnidx2 < mnidx1))
                mnidx1 = mnidx2;
            printf("%d\n", mnidx1+1);
            //printf("[%d %d] [%d %d]\n", ll, lr, rl, rr);
            //printf("%d %lld %lld ++\n", mnidx1+1, dist(D[i], D[mnidx1]), dist(D[i], D[mnidx2]));
            for(j = 0, k = i; j < n; j++, k++) {
                //printf("%lld ", dist(D[i], D[k]));
                if(dist(D[i], D[j]) > mxdist) {
                    mxdist = dist(D[i], D[j]);
                    mnidx2 = j;
                }
            }
            if(mnidx1 != mnidx2)    puts("err");
            rr += 3000, ll -= 3000;
            //printf("*%d %lld\n", mnidx1+1, dist(D[i], D[mnidx1]));
        }
    }
    return 0;
}
/*
14
50 14
483 3
1014 0
9016 2
9596 5
9959 14
9996 653
9995 911
9986 986
5965 999
392 999
205 958
75 907
52 512
5
0 0
-4 2
-2 4
2 4
4 2
3
0 0
1 0
0 10
8
3 2
2 3
-2 3
-3 2
-3 -2
-2 -3
2 -3
3 -2
*/
