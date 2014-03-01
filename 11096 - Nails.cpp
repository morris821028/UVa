#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct Pt {
    double x, y;
};
bool cmp(Pt a, Pt b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
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
    return m-1;
}
int main() {
    int t, n, i, j;
    double len, sum;
    scanf("%d", &t);
    while(t--) {
        scanf("%lf %d", &len, &n);
        Pt p[1005], ch[1005];
        for(i = 0; i < n; i++)
            scanf("%lf %lf", &p[i].x, &p[i].y);
        int m = monotone(p, n, ch);
        sum = 0;
        for(i = 0; i < m; i++) {
            sum += sqrt(pow(ch[i].x-ch[i+1].x, 2)+pow(ch[i].y-ch[i+1].y, 2));
        }
        if(len > sum)
            printf("%.5lf\n", len);
        else
            printf("%.5lf\n", sum);
    }
    return 0;
}
