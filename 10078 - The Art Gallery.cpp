#include <stdio.h>
typedef struct {
    int x, y;
} Pt;
int cross(Pt o, Pt a, Pt b) {
    return (a.x - o.x)*(b.y - o.y) -
        (a.y - o.y)*(b.x - o.x);
}
int main() {
    int n, i;
    Pt D[100];
    while(scanf("%d", &n), n) {
        for(i = 0; i < n; i++)
            scanf("%d %d", &D[i].x, &D[i].y);
        D[n] = D[0], D[n+1] = D[1];
        if(cross(D[0], D[1], D[2]) >= 0) {
            for(i = 0; i < n; i++)
                if(cross(D[i], D[i+1], D[i+2]) < 0)
                    break;
        } else {
            for(i = 0; i < n; i++)
                if(cross(D[i], D[i+1], D[i+2]) > 0)
                    break;
        }
        if(i != n)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
