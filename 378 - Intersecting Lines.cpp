#include <stdio.h>
struct Point {
    int x, y;
};
struct Segment {
    Point s, e;
};
void solve(Segment a, Segment b) {
    int a1, b1, c1, a2, b2, c2;
    int D, Dx, Dy;
    a1 = a.s.y-a.e.y, b1 = -a.s.x+a.e.x;
    a2 = b.s.y-b.e.y, b2 = -b.s.x+b.e.x;
    c1 = a1*a.s.x + b1*a.s.y;
    c2 = a2*b.s.x + b2*b.s.y;
    D = a1*b2-a2*b1;
    Dx = c1*b2 - c2*b1;
    Dy = a1*c2 - a2*c1;
    if(!D && (Dx || Dy))
        puts("NONE");
    else if(!D && !Dx && !Dy)
        puts("LINE");
    else
        printf("POINT %.2lf %.2lf\n", (double)Dx/D, (double)Dy/D);
}
int main() {
    int t;
    scanf("%d", &t);
    puts("INTERSECTING LINES OUTPUT");
    while(t--) {
        Segment a, b;
        scanf("%d %d %d %d", &a.s.x, &a.s.y, &a.e.x, &a.e.y);
        scanf("%d %d %d %d", &b.s.x, &b.s.y, &b.e.x, &b.e.y);
        solve(a, b);
    }
    puts("END OF OUTPUT");
    return 0;
}
