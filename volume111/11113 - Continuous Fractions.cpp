#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define NLEN 25
class UINT70 {
    public:
        int d[NLEN], length, ZF;
        UINT70(const char *s) {
            int i, j;
            memset(d, 0, sizeof(d));
            for(i = 0; s[i]; i++)
                d[i] = s[i]-'0';
            length = i;
            for(j = i-1, i = 0; j > i; j--, i++)
                swap(d[i], d[j]);
            if(length == 1 && d[0] == 0)
                ZF = 1;
            else
                ZF = 0;
        }
        UINT70() {
            length = 1;
            memset(d, 0, sizeof(d));
            ZF = 1;
        }
        UINT70 operator-(const UINT70 &y) {
            int i;
            UINT70 ans;
            memcpy(ans.d, d, sizeof(d));
            for(i = 0; i < y.length; i++)
                ans.d[i] -= y.d[i];
            ans.carry();
            return ans;
        }
        UINT70 operator*(const UINT70 &y) {
            int i, j;
            UINT70 ans;
            for(i = 0; i < length; i++) {
                for(j = 0; j < y.length; j++) {
                    if(i+j < NLEN)
                    ans.d[i+j] += (this->d[i])*y.d[j];
                }
            }
            ans.carry();
            return ans;
        }
        UINT70 operator/(const UINT70 &y) {
            int i, j, x[NLEN];
            UINT70 ans;
            memcpy(x, d, sizeof(d));
            for(i = length-y.length; i >= 0; i--) {
                while(check(x, y.d, y.length, i)) {
                    ans.d[i]++;
                    for(j = 0; j < y.length+1; j++) {
                        x[i+j] -= y.d[j];
                        if(x[i+j] < 0) {
                            x[i+j+1]--;
                            x[i+j] += 10;
                        }
                    }
                }
            }
            ans.carry();
            return ans;
        }
        UINT70 operator%(const UINT70 &y) {
            int i, j, x[NLEN];
            UINT70 ans;
            memcpy(x, d, sizeof(d));
            for(i = length-y.length; i >= 0; i--) {
                while(check(x, y.d, y.length, i)) {
                    for(j = 0; j < y.length+1; j++) {
                        x[i+j] -= y.d[j];
                        if(x[i+j] < 0) {
                            x[i+j+1]--;
                            x[i+j] += 10;
                        }
                    }
                }
            }
            for(i = NLEN-1; i >= 0; i--)
                ans.d[i] = x[i];
            ans.carry();
            return ans;
        }
        void c_str(char *p) {
            int i;
            for(i = length-1; i >= 0; i--)
                *p++ = d[i]+'0';
            *p = '\0';
        }
    private:
        void carry() {
            int i;
            for(i = 0; i < NLEN-1; i++) {
                while(d[i] < 0)
                    d[i+1]--, d[i] += 10;
                d[i+1] += d[i]/10;
                d[i] %= 10;
            }
            for(i = NLEN-1; i > 0 && d[i] == 0; i--);
            length = i+1;
            if(length == 1 && d[0] == 0)
                ZF = 1;
            else
                ZF = 0;
        }
        int check(const int x[], const int y[], int ly, int shift) {
            int i;
            for(i = ly; i >= 0; i--) {
                if(x[i+shift] < y[i])
                    return 0;
                if(x[i+shift] > y[i])
                    return 1;
            }
            return 1;
        }
};
char g[256][512];
char buf[30];
int N, M;
int build(UINT70 p, UINT70 q, int x, int y) {
    UINT70 pdivq, pmodq;
    pdivq = p/q;
    pmodq = p%q;
    if(pmodq.ZF) {
        UINT70 one("1");
        pdivq = pdivq - one;
    }
    pdivq.c_str(buf);
    sprintf(g[x+1]+y, "%s.+.", buf);
    int ty = y;
    while(g[x+1][ty] != '\0')   ty++;
    g[x+1][ty] = '.';
    int i, len;
    if(!pmodq.ZF) {
        len = build(q, pmodq, x+2, ty);
        for(i = 0; i < len; i++)
            g[x+1][i+ty] = '-';
        g[x][ty+(len-1)/2] = '1';
        len = len + ty-y;
    } else {
        len = 1;
        g[x][ty] = '1';
        g[x+1][ty] = '-';
        g[x+2][ty] = '1';
        N = x+3;
        len = len + ty-y;
    }
    return len;
}
int main() {
    long long p, q;
    int cases = 0;
    char s1[150], s2[150];
    while(scanf("%s %s", s1, s2) == 2) {
        UINT70 p(s1), q(s2);
        if(p.ZF)  break;
        memset(g, '.', sizeof(g));
        printf("Case %d:\n", ++cases);
        printf("%s / %s\n", s1, s2);
        M = build(p, q, 0, 0);
        int i, j;
        for(i = 0; i < N; i++) {
            g[i][M] = '\0';
            puts(g[i]);
        }
    }
    return 0;
}
/*
99999999999999999999 99999999999999999998
*/
