#include <stdio.h>
#include <string.h>

int main() {
    char s[1024];
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int len = strlen(s);
        short x[1024] = {}, y[1024] = {};
        int i, j;
        for(i = 0, j = len-1; i < len; i++, j--)
            x[i] = s[j]-'0';
        int xlen = len, ylen = 0;
        while(xlen >= 0 && x[xlen] == 0) xlen--;
        for(j = (len-1)/2, i = j*2; j >= 0; j--, i -= 2) {
            ylen++;
            for(int p = ylen; p >= 1; p--)
                y[p] = y[p-1];
            y[0] = 0;
            if(xlen < i) {
                putchar('0');
                continue;
            }
            int l = 0, r = 9, p;
            short z[1024]; // z = (y*10 + p)*p;
            while(l <= r) {
                p = (l+r)/2;
                y[0] = p;
                z[0] = 0;
                for(int q = 0; q <= ylen+5; q++) {
                    z[q] += p*y[q];
                    z[q+1] = z[q]/10;
                    z[q] %= 10;
                }
                int chflag = 0;
                for(int q = ylen+5; q >= 0; q--) {
                    if(z[q] > x[i+q]) {
                        chflag = 1;
                        break;
                    } else if(z[q] < x[i+q]) {
                        chflag = 0;
                        break;
                    }
                }
                if(chflag)
                    r = p-1;
                else
                    l = p+1;
            }
            p = l-1;
            y[0] = p;
            z[0] = 0;
            for(int q = 0; q <= ylen+5; q++) {
                z[q] += p*y[q];
                z[q+1] = z[q]/10;
                z[q] %= 10;
            }
            for(int q = ylen+5; q >= 0; q--)
                x[i+q] -= z[q];
            for(int q = 0; q <= ylen+5; q++) {
                while(x[i+q] < 0)
                    x[i+q] += 10, x[i+q+1]--;
            }
            y[0] += p;
            for(int q = 0; q <= ylen+5; q++) {
                if(y[q] >= 10) {
                    y[q+1] += y[q]/10;
                    y[q] %= 10;
                }
            }
            ylen += 5;
            while(ylen >= 0 && y[ylen] == 0)    ylen--;
            while(xlen >= 0 && x[xlen] == 0)    xlen--;
            putchar(p+'0');
        }
        puts("");
        if(t)
            puts("");
    }
    return 0;
}
