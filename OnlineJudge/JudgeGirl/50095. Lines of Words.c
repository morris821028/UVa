#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readchar() {
#define N 1048576
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
#undef N
}
int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
#define MAXS (1<<24)
#define MAXW (1<<16)
#define MAXN (1<<10)
int read(char **sptr) {
    static char c;
    while ((c = readchar()) < ' ')    {if(c == EOF) return -1;}
    **sptr = c, (*sptr)++;
    while ((c = readchar()) > ' ')
        **sptr = c, (*sptr)++;
    **sptr = '\0', (*sptr)++;
    return c == '\n' ? -1 : 0;
}
int main() {
    int n, m;
    static char sbuf[MAXS], obuf[MAXS];
    static char **R[MAXN], *H[MAXW];
    while (ReadInt(&n)) {
        char *sptr = sbuf;
        for (int i = 0, k = 0; i < n; i++) {
            R[i] = &H[k];
            int nextline;
            do {
                H[k] = sptr, k++;
                nextline = read(&sptr);
            } while (nextline >= 0);
			H[k] = NULL, k++;
        }
	
		ReadInt(&m);	
		while (m--) {
			int x, y, a, b;
			ReadInt(&x), ReadInt(&y);
			ReadInt(&a), ReadInt(&b);
			char *tmp;
			tmp = R[x][y], R[x][y] = R[a][b], R[a][b] = tmp;
		}

		for (int i = 0; i < n; i++) {
			char **p = R[i];
			char *optr = obuf;
			for (int j = 0; p[j]; j++) {
				char *s = p[j]; 
				for (int k = 0; s[k]; k++)
					*optr = s[k], optr++;
				*optr = ' ', optr++;
			}
			optr--, *optr = '\0';
			puts(obuf);
		}
    }
    return 0;
}
/*
 
*/


