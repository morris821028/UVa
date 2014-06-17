#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int main() {
    int testcase;
    char s[2048];
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%s", s);
        int x[505] = {}, y[505] = {}, op;
        int z[1005] = {};
        int slen = strlen(s), xlen = 0, ylen = 0, zlen = 0;
        int i, j;
        for(i = slen-1; i >= 0; i--) {
            if(s[i] == '+' || s[i] == '-' || s[i] == '*') {
                op = s[i];
                break;
            }
            y[ylen++] = s[i]-'0';
        }
        for(i--; i >= 0; i--)
            x[xlen++] = s[i]-'0';
        int plen = max(xlen, ylen+1);
        if(op == '+') {
            for(i = 0; i < xlen; i++)
                z[i] = x[i];
            for(i = 0; i < ylen; i++)
                z[i] += y[i];
            zlen = max(xlen, ylen)+1;
            for(i = 0; i <= zlen; i++) {
                if(z[i] >= 10)
                    z[i+1] += z[i]/10, z[i] %= 10;
            }
            zlen++;
            while(zlen > 0 && z[zlen] == 0)
                zlen--;
            plen = max(plen, zlen+1);
            for(i = xlen; i < plen; i++)
                putchar(' ');
            for(i = xlen-1; i >= 0; i--)
                putchar(x[i]+'0');
            puts("");
            for(i = ylen+1; i < plen; i++)
                putchar(' ');
            putchar('+');
            for(i = ylen-1; i >= 0; i--)
                putchar(y[i]+'0');
            puts("");
            for(i = 0; i < plen; i++)
                putchar('-');
            puts("");
            for(i = zlen+1; i < plen; i++)
                putchar(' ');
            for(i = zlen; i >= 0; i--)
                putchar(z[i]+'0');
            puts("");
            puts("");
            continue;
        }
        if(op == '-') {
            for(i = 0; i < xlen; i++)
                z[i] = x[i];
            for(i = 0; i < ylen; i++)
                z[i] -= y[i];
            zlen = max(xlen, ylen)+1;
            for(i = 0; i <= zlen; i++) {
                while(z[i] < 0) {
                    z[i+1]--;
                    z[i] += 10;
                }
            }
            zlen++;
            while(zlen > 0 && z[zlen] == 0)
                zlen--;
            plen = max(plen, zlen+1);
            for(i = xlen; i < plen; i++)
                putchar(' ');
            for(i = xlen-1; i >= 0; i--)
                putchar(x[i]+'0');
            puts("");
            for(i = ylen+1; i < plen; i++)
                putchar(' ');
            putchar('-');
            for(i = ylen-1; i >= 0; i--)
                putchar(y[i]+'0');
            puts("");
            int pp = max(ylen+1, zlen+1);
            for(i = pp; i < plen; i++)
                putchar(' ');
            for(i = pp-1; i >= 0; i--)
                putchar('-');
            puts("");
            for(i = zlen+1; i < plen; i++)
                putchar(' ');
            for(i = zlen; i >= 0; i--)
                putchar(z[i]+'0');
            puts("");
            puts("");
            continue;
        }
        if(op == '*') {
            short tmp[505][1035] = {}, tlen;
            zlen = xlen+ylen+5;
            for(i = 0; i < ylen; i++) {
                if(y[i] == 0)   continue;
                for(j = 0; j < xlen; j++) {
                    tmp[i][i+j] = y[i]*x[j];
                    z[i+j] += y[i]*x[j];
                }
                tlen = i+xlen+5;
                for(j = 0; j < tlen; j++) {
                    if(tmp[i][i+j] >= 10)
                        tmp[i][i+j+1] += tmp[i][i+j]/10, tmp[i][i+j] %= 10;
                }
            }
            for(i = 0; i <= zlen; i++) {
                if(z[i] >= 10) {
                    z[i+1] += z[i]/10;
                    z[i] %= 10;
                }
            }
            zlen++;
            while(zlen > 0 && z[zlen] == 0)
                zlen--;
            plen = max(plen, zlen+1);
            for(i = xlen; i < plen; i++)
                putchar(' ');
            for(i = xlen-1; i >= 0; i--)
                putchar(x[i]+'0');
            puts("");
            for(i = ylen+1; i < plen; i++)
                putchar(' ');
            putchar('*');
            for(i = ylen-1; i >= 0; i--)
                putchar(y[i]+'0');
            puts("");
            if(ylen > 1) {

            for(i = 0; i < ylen; i++) {
                if(y[i])
                for(j = i; j <= i+xlen; j++) {
                    if(tmp[i][j] >= 10)
                        tmp[i][j+1] += tmp[i][j]/10, tmp[i][j] %= 10;
                }
                tlen = i+xlen+5;
                while(tlen > i && tmp[i][tlen] == 0)    tlen--;
                if(i == 0) {
                    int pp = max(ylen+1, tlen+1);
                    for(j = pp; j < plen; j++)
                        putchar(' ');
                    for(j = pp-1; j >= 0; j--)
                        putchar('-');
                    puts("");
                }
                for(j = tlen+1; j < plen; j++)
                    putchar(' ');
                for(j = tlen; j >= i; j--)
                    putchar(tmp[i][j]+'0');
                puts("");
            }
            }
            for(i = zlen+1; i < plen; i++)
                putchar(' ');
            for(i = 0; i <= zlen; i++)
                putchar('-');
            puts("");
            for(i = zlen+1; i < plen; i++)
                putchar(' ');
            for(i = zlen; i >= 0; i--)
                putchar(z[i]+'0');
            puts("");
            puts("");
            continue;
        }
    }
    return 0;
}
/*
50
123+123
123-123
1+99999
123456*4
4*123456
10500*50
12354*56
10000-1
123-123
*/
