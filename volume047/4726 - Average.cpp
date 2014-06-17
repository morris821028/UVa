#include <stdio.h>
#include <string.h>
struct Pt {
    long long x, y;
    Pt(int x, int y) : x(x), y(y) {}
    Pt() {};
};
long long cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
double sol(int n, int m, int sum[]) {
    double ans = 0, tmp;
    Pt s[10005];
    int p = -1, h = 0, i;
    int ll, rr;
    for(i = m; i <= n; i++) {
        Pt r(i-m, sum[i-m]);
        while(p > h && cross(s[p-1], s[p], r) < 0)
            p--;
        s[++p] = r;
        while(p > h && (sum[i]-s[h].y)*(i-s[h+1].x) <
              (sum[i]-s[h+1].y)*(i-s[h].x))
            h++;
        tmp = (double)(sum[i]-s[h].y)/(i-s[h].x);
        if(tmp >= ans) {
            if(tmp > ans) {
                ans = tmp;
                ll = s[h].x;
                rr = i;
            } else if(i - s[h].x < rr - ll) {
                ll = s[h].x;
                rr = i;
            }
        }
    }
    printf("%d %d %lf\n", ll+1, rr, ans);
    return ans;
}
int main() {
    int t, n, m, i;
    char s[100005];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %s", &n, &m, s);
        int len = strlen(s), sum[100005] = {};
        for(i = 1; i <= len; i++) {
            sum[i] = s[i-1]-'0';
            sum[i] += sum[i-1];
        }
        sol(len, m, sum);
    }
    return 0;
}
/*
2
34 5
0010101101101101000101011011011010
20 4
11101111110111101111110111110000
*/
