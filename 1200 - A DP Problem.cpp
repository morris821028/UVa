#include <stdio.h>
#include <math.h>
void parse(char *s, int& A, int& B) {
    A = 0, B = 0;
    int i, g = 0, f = 0, neg = 1;
    for(i = 0; s[i]; i++) {
        if(s[i] == 'x') {
            if(g)
                A += neg*f;
            else
                A += neg;
            g = 0, f = 0, neg = 1;
        } else {
            if(s[i] == '-') {
                if(g)
                    B += neg*f;
                g = 0, f = 0;
                neg = -1;
            } else if(s[i] == '+') {
                if(g)
                    B += neg*f;
                g = 0, f = 0;
                neg = 1;
            } else
                f = f*10 + s[i]-'0', g = 1;
        }
    }
    if(g)
        B += neg*f;
}
int main() {
    int t, i;
    scanf("%d", &t);
    char s1[502], *s2;
    while(t--) {
        scanf("%s", s1);
        for(i = 0; s1[i]; i++) {
            if(s1[i] == '=') {
                s2 = s1+i+1;
                s1[i] = '\0';
                break;
            }
        }
        int la, lb, ra, rb;
        parse(s1, la, lb);
        parse(s2, ra, rb);
        if(la == ra && lb == rb)
            puts("IDENTITY");
        else if(la == ra && lb != rb)
            puts("IMPOSSIBLE");
        else
            printf("%d\n", (int)floor((double)(rb-lb)/(la-ra)));
    }
    return 0;
}
