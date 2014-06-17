#include <cstdio>
#include <algorithm>
using namespace std;
typedef struct {
    int x, y;
} Pt;
Pt P[500000], H[500000];
bool cmp(Pt a, Pt b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
int cross(Pt &o, Pt &a, Pt &b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
void solve(int n) {
    sort(P, P+n, cmp);
    int i, j, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(H[m-2], H[m-1], P[i]) <= 0)
            m--;
        H[m++] = P[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(H[m-2], H[m-1], P[i]) <= 0)
            m--;
        H[m++] = P[i];
    }
    m--;
    int ans = 0, tmp, now;
    for(i = 0, j= 1; i < m; i++) {
        while(1) {
            now = (H[i].x-H[j].x)*(H[i].x-H[j].x)+
            (H[i].y-H[j].y)*(H[i].y-H[j].y);
            j++;
            if(j >= m)  j = 0;
            tmp = (H[i].x-H[j].x)*(H[i].x-H[j].x)+
            (H[i].y-H[j].y)*(H[i].y-H[j].y);
            if(tmp < now) {
                j--;
                if(j < 0)   j = m-1;
                break;
            }
        }
        if(now > ans)   ans = now;
    }
    printf("%d\n", ans);
}
int main() {
    int t, x, y, w;
    scanf("%d", &t);
    while(t--) {
        int n, m = 0;
        scanf("%d", &n);
        while(n--) {
            scanf("%d %d %d", &x, &y, &w);
            P[m].x = x, P[m++].y = y;
            P[m].x = x+w, P[m++].y = y;
            P[m].x = x, P[m++].y = y+w;
            P[m].x = x+w, P[m++].y = y+w;
        }
        solve(m);
    }
    return 0;
}
