#include <stdio.h>
#include <string.h>
typedef struct {
    char p[6];
} Dice;
int cmp(Dice x, Dice y) {
    static int i;
    for(i = 0; i < 6; i++)
        if(x.p[i] != y.p[i])
            return x.p[i] - y.p[i];
    return 0;
}
Dice MinExp(Dice x) {
    Dice y = x;
    int i, j, t;
    for(i = 0; i < 4; i++) { /*x_rotate*/
        for(j = 0; j < 4; j++) { /*y_rotate*/
            t = x.p[2], x.p[2] = x.p[0], x.p[0] = x.p[3];
            x.p[3] = x.p[5], x.p[5] = t;
            if(cmp(y, x) > 0)   y = x;
        }
        for(j = 0; j < 4; j++) { /*z_rotate*/
            t = x.p[0], x.p[0] = x.p[1], x.p[1] = x.p[5];
            x.p[5] = x.p[4], x.p[4]  = t;
            if(cmp(y, x) > 0)   y = x;
        }
        t = x.p[1], x.p[1] = x.p[3], x.p[3] = x.p[4];
        x.p[4] = x.p[2], x.p[2] = t;
            if(cmp(y, x) > 0)   y = x;
    }
    return y;
}
int main() {
    char s[50], i;
    Dice a, b;
    while(gets(s)) {
        for(i = 0; i < 6; i++)
            a.p[i] = s[i], b.p[i] = s[i+6];
        a = MinExp(a);
        b = MinExp(b);
        if(!memcmp(a.p, b.p, 6))
            puts("TRUE");
        else
            puts("FALSE");
    }
    return 0;
}
