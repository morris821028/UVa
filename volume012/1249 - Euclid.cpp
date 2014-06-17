#include <stdio.h>
#include <math.h>
struct Pt {
    double x, y;
    void scan() {
        scanf("%lf %lf", &x, &y);
    }
};
#define eps 1e-8
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double dist(Pt a, Pt b) {
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}
int main() {
    Pt in[6];
    int i, j, k;
    while(1) {
        int eof = 1;
        for(i = 0; i < 6; i++) {
            in[i].scan();
            if(fabs(in[i].x) > eps || fabs(in[i].y) > eps)
                eof = 0;
        }
        if(eof) break;
        double areaDEF = fabs(cross(in[3], in[4], in[5])/2);
        double areaABC = fabs(cross(in[0], in[1], in[2])/2);
        double distAB = dist(in[0], in[1]);
        double distAC = dist(in[0], in[2]);
        double sintheta = areaABC*2/distAB/distAC;
        double distAH = areaDEF/sintheta/distAB;
        Pt H, G;
        H.x = in[0].x + (in[2].x-in[0].x)*distAH/distAC;
        H.y = in[0].y + (in[2].y-in[0].y)*distAH/distAC;
        G.x = H.x + (in[1].x-in[0].x);
        G.y = H.y + (in[1].y-in[0].y);
        printf("%.3lf %.3lf %.3lf %.3lf\n", G.x, G.y, H.x, H.y);
    }
    return 0;
}
/*
0 0 5 0 0 5 0 0 0 1 1 0
0 0 5 0 0 5 3 2 7 2 0 4
1.3 2.6 12.1 4.5 8.1 13.7 2.2 0.1 9.8 6.6 1.9 6.7
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
*/
