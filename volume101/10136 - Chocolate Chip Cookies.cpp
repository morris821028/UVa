#include <stdio.h>
#include <math.h>
#define eps 1e-6
struct Pt {
    double x, y;
};
double dist(Pt a, Pt b) {
    return pow(a.x-b.x,2)+pow(a.y-b.y,2);
}
Pt p[205];
int check(int n, Pt c) {
    int i, cnt = 0;
    for(i = 0; i < n; i++) {
        if(dist(c, p[i]) <= 2.5*2.5+eps)
            cnt++;
    }
    return cnt;
}
int main() {
    int t, i, j;
    char s[105];
    scanf("%d", &t);
    while(getchar() != '\n');
    while(getchar() != '\n');
    while(t--) {
        int n = 0;
        while(gets(s) && s[0]) {
            sscanf(s, "%lf %lf", &p[n].x, &p[n].y);
            n++;
        }
        int ans = 0, tmp;
        Pt m, C;
        for(i = 0; i < n; i++) {
            C = p[i];
            tmp = check(n, C);
            if(tmp > ans)   ans = tmp;
            for(j = i+1; j < n; j++) {
                Pt A = p[i], B = p[j];
                double distAB = sqrt(dist(A, B));
                if(distAB <= 5+eps) {
                    double distmC = sqrt(2.5*2.5-distAB*distAB/4+eps);
                    double vx = A.y-B.y, vy = B.x-A.x, vv;
                    m.x = (A.x+B.x)/2, m.y = (A.y+B.y)/2;
                    vv = sqrt(vx*vx + vy*vy);
                    vx /= vv, vy /= vv;
                    C.x = m.x + vx*distmC, C.y = m.y + vy*distmC;
                    tmp = check(n, C);
                    if(tmp > ans)   ans = tmp;
                    C.x = m.x - vx*distmC, C.y = m.y - vy*distmC;
                    tmp = check(n, C);
                    if(tmp > ans)   ans = tmp;
                }
            }
        }
        printf("%d\n", ans);
        if(t)   puts("");
    }
    return 0;
}
