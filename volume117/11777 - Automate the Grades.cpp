#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int t, test = 0;
    scanf("%d", &t);
    while(t--) {
        int a, b, c, d, g[3];
        double f = 0;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        f = a*5*0.2 + b*5*0.2 + c*10/3.0*0.3 + d*10*0.1;
        scanf("%d %d %d", &g[0], &g[1], &g[2]);
        sort(g, g+3);
        f += (g[1]+g[2])/2*5*0.2;
        printf("Case %d: ", ++test);
        if(f >= 90)
            puts("A");
        else if(f >= 80)
            puts("B");
        else if(f >= 70)
            puts("C");
        else if(f >= 60)
            puts("D");
        else
            puts("F");
    }
    return 0;
}
