#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define eps 1e-8
struct Pt {
   	long long x, y;
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)
            return x < a.x;
        return y < a.y;
    }
};
long long cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
int main() {
	freopen("test.txt", "r+t", stdin);
	freopen("testout.txt", "w+t", stdout);  
    int n, m, o;
    int i, j, p, q;
    Pt a[10005], b[10005];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%lld %lld", &a[i].x, &a[i].y);
        int m = monotone(n, a, b);
        printf("%d\n", m);
        for(i = 0; i < m; i++)
        	printf("%lld %lld\n", b[i].x, b[i].y);
    }
    return 0;
}

