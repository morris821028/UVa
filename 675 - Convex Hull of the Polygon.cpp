#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Pt {
    long long x, y;
};
double cross(Pt o, Pt a, Pt b) {
    return ((double)(a.x-o.x))*(b.y-o.y)-((double)(a.y-o.y))*(b.x-o.x);
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
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m;
}
Pt p[500000], ch[500000];
int main() {
    char s[105];
    int n = 0, i;
    while(scanf("%lld, %lld", &p[n].x, &p[n].y) == 2)
        n++;
    n = monotone(p, n, ch);
    for(i = 0; i < n; i++)
        printf("%lld, %lld\n", ch[i].x, ch[i].y);
    return 0;
}
