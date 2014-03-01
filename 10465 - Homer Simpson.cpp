#include <stdio.h>

int main() {
    int n, m, t;
    while(scanf("%d %d %d", &n, &m, &t) == 3) {
        int a2 = 0, t2 = 0xffff, i;
        for(i = t/n; i >= 0; i--) {
            int ta2 = i+(t-n*i)/m;
            int tt2 = t-n*i-(t-n*i)/m*m;
            if(tt2 < t2 || (tt2 == t2 && ta2 > a2))
                t2 = tt2, a2 = ta2;
        }
        printf("%d", a2);
        if(t2)  printf(" %d", t2);
        puts("");
    }
    return 0;
}
