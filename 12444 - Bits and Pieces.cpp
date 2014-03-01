#include <stdio.h>
void solve(int c, int d) {
    int i, a, b;
    for(i = 30; i >= 0; i--) {
        if((c&(1<<i)) != 0 && (d&(1<<i)) == 0) {
            puts("-1");
            return;
        }
    }
    a = c, b = c;
    int flag = 0;
    for(i = 30; i >= 0; i--) {
        if((c&(1<<i)) == 0) {
            if((d&(1<<i)) != 0) {
                if(flag)
                    a |= 1<<i;
                else
                    b |= 1<<i;
                flag = 1;
            }
        }
    }
    printf("%d %d\n", a, b);
}
int main() {
    int t, c, d;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &c, &d);
        solve(c, d);
    }
    return 0;
}
