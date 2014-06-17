#include <stdio.h>
int p[5500], pt = 0;
char pstr[5500][7];
void sieve() {
    int i, j;
    char mark[50000] = {};
    for(i = 2; i < 46340; i++)
        if(!mark[i]) {
            for(j = i+i; j < 46340; j += i)
                mark[j] = 1;
            sprintf(pstr[pt], "%d", i);
            p[pt++] = i;
        }
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    sieve();
    int n, i, j;
    char buf[1005], *pb;
    while(ReadInt(&n) && n) {
        printf("%d = ", n);
        if(n == 1) {
            puts("1");
            continue;
        }
        if(n == -1) {
            puts("-1");
            continue;
        }
        int first = 0;
        if(n < 0)
            printf("-1"), first = 1, n = -n;
        pb = buf;
        for(i = 0; i < pt && p[i]*p[i] <= n; i++) {
            while(n%p[i] == 0) {
                if(first)
                    *pb++ = ' ', *pb++ = 'x', *pb++ = ' ';
                //putchar(' '), putchar('x'), putchar(' ');
                else first = 1;
                if(pstr[i][1] == '\0')
                    *pb++ = pstr[i][0];
                    //putchar(pstr[i][0]);
                else if(pstr[i][2] == '\0')
                    *pb++ = pstr[i][0], *pb++ = pstr[i][1];
                    //putchar(pstr[i][0]), putchar(pstr[i][1]);
                else if(pstr[i][3] == '\0')
                    *pb++ = pstr[i][0], *pb++ = pstr[i][1], *pb++ = pstr[i][2];
                    //putchar(pstr[i][0]), putchar(pstr[i][1]), putchar(pstr[i][2]);
                else if(pstr[i][4] == '\0')
                    *pb++ = pstr[i][0], *pb++ = pstr[i][1], *pb++ = pstr[i][2],
                    *pb++ = pstr[i][3];
                    //putchar(pstr[i][0]), putchar(pstr[i][1]), putchar(pstr[i][2]),
                    //putchar(pstr[i][3]);
                else
                    *pb++ = pstr[i][0], *pb++ = pstr[i][1], *pb++ = pstr[i][2],
                    *pb++ = pstr[i][3], *pb++ = pstr[i][4];
                    //putchar(pstr[i][0]), putchar(pstr[i][1]), putchar(pstr[i][2]),
                    //putchar(pstr[i][3]), putchar(pstr[i][4]);
                n /= p[i];
            }
        }
        if(n != 1) {
            if(first)
                *pb++ = ' ', *pb++ = 'x', *pb++ = ' ';
                //putchar(' '), putchar('x'), putchar(' ');
            else first = 1;
            sprintf(pb, "%d", n);
        } else
            *pb = '\0';
        puts(buf);
    }
    return 0;
}
