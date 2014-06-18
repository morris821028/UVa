#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Pt {
    long long x, y;
};
#define eps 1e-8
long long cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
bool cmp(Pt a, Pt b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
int monotone(Pt p[], int n, Pt ch[]) {
    sort(p, p+n, cmp);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) < 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-2, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) < 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
Pt p[100005], ch[200005];
int main() {
    int t, n, m, i, j;
    char cc;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0, j = 0; i < n; i++) {
            scanf("%lld %lld %c", &p[j].x, &p[j].y, &cc);
            if(cc == 'Y')   j++;
        }
        m = monotone(p, j, ch);
        printf("%d\n", m);
        for(i = 0; i < m; i++)
            printf("%lld %lld\n", ch[i].x, ch[i].y);
    }
    return 0;
}
