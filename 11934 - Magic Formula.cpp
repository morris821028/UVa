#include <stdio.h>

int main() {
    int a, b, c, d, L;
    while(scanf("%d %d %d %d %d", &a, &b, &c, &d, &L)) {
        if(a == 0 && b == 0 && c == 0 && d == 0 && L == 0)
            break;
        int i, ans = 0;
        for(i = 0; i <= L; i++) {
            if((a*i*i+b*i+c)%d == 0)
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
