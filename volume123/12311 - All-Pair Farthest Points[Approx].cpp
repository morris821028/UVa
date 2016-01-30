#include <bits/stdc++.h>
using namespace std;
struct Pt {
    long long x, y;
    int label;
    Pt(long long a = 0, long long b = 0, int c = 0):
        x(a), y(b), label(c) {}
    Pt operator-(const Pt &a) {
        return Pt(x-a.x, y-a.y);
    }
};
long long cross(Pt a, Pt b) {
    return a.x*b.y - a.y*b.x;
}
long long cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
long long dist(Pt &a, Pt &b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

const int MAXN = 131072;
Pt D[MAXN];
int mnidx[MAXN];
long long mxdist[MAXN];

void solve(int n) {
	long long d;
	for (int i = 0, j = 1; i < n; i++) {
		while (dist(D[i], D[(j+1)%n]) > dist(D[i], D[j]))
			j = (j+1)%n;
		for (int k = -4; k <= 4; k++) {
			int p = D[i].label;
			int q = D[((j+k)%n+n)%n].label;
			d = dist(D[i], D[((j+k)%n+n)%n]);
			if (d > mxdist[p] || (d == mxdist[p] && q < mnidx[p]))
				mnidx[p] = q, mxdist[p] = d;
		}
	}	
}
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &D[i].x, &D[i].y);
            D[i].label = i;
        }
        
        memset(mnidx, 0, sizeof(mnidx));
        memset(mxdist, 0, sizeof(mxdist));
        
        solve(n);
        reverse(D, D+n);
        solve(n);
		for (int i = 0; i < n; i++)
			printf("%d\n", mnidx[i]+1);
    }
    return 0;
}

