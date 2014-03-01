#include <stdio.h>
#include <algorithm>
using namespace std;
struct Pt {
    long long x, y;
    char s[2];
};
int Inline(Pt a, Pt b, Pt c) {
    long long ax, ay, bx, by;
    ax = min(a.x, b.x);
    ay = min(a.y, b.y);
    bx = max(a.x, b.x);
    by = max(a.y, b.y);
    return ax <= c.x && c.x <= bx &&
            ay <= c.y && c.y <= by &&
            (a.x-c.x)*(b.y-c.y) == (a.y-c.y)*(b.x-c.x);
}
long long calcArea(Pt a, Pt b, Pt c) {
    long long tmp = (c.y-a.y)*(b.x-a.x)-(b.y-a.y)*(c.x-a.x);
    if(tmp < 0) tmp = -tmp;
    return tmp;
}
int main() {
    int n, i, j, k, l;
    Pt p[105];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%s %lld %lld", p[i].s, &p[i].x, &p[i].y);
        int mxarea = 0;
        char res[4] = {};
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                for(k = j+1; k < n; k++) {
                    int tmp = calcArea(p[i], p[j], p[k]), flag = 0;
                    if(tmp <= mxarea)
                        continue;
                    for(l = 0; l < n && !flag; l++) {
                        if(i == l || j == l || k == l)
                            continue;
                        if(Inline(p[i], p[j], p[l]) || Inline(p[j], p[k], p[l]) ||
                           Inline(p[k], p[i], p[l]))
                           flag = 1;
                        if(calcArea(p[i], p[j], p[l])+
                           calcArea(p[j], p[k], p[l])+
                           calcArea(p[k], p[i], p[l]) == tmp) {
                           flag = 1;
                        }
                    }
                    if(!flag) {
                        mxarea = tmp;
                        res[0] = p[i].s[0];
                        res[1] = p[j].s[0];
                        res[2] = p[k].s[0];
                    }
                }
            }
        }
        sort(res, res+3);
        puts(res);
    }
    return 0;
}
