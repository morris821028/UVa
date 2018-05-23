#include <bits/stdc++.h> 
using namespace std;

const int MAXQ = 65536;
const int MAXM = 50005;
const int MAXN = 205;
const int MAXC = 10;
struct Shape {
	int type;
	int xc, yc, c;
	int a, b;
	Shape(int type=0, int c = 0, int xc=0, int yc=0, int a=0, int b=0):
		type(type), c(c), xc(xc), yc(yc), a(a), b(b) {}
}; 

Shape shape[MAXQ];
int n, m;
int16_t jump[MAXN][(MAXM>>5)+1];
uint32_t mask[MAXN][(MAXM>>5)+1]; 
int stat[MAXC];

void init(int n, int m) {
	int cm = (m>>5)+1;
	for (int j = 0; j <= cm; j++)
		jump[0][j] = j;
	for (int i = 1; i < n; i++)
		memcpy(jump[i], jump[0], sizeof(jump[0][0])*(cm+1));

	for (int i = 0; i < n; i++)
		memset(mask[i], 0, sizeof(mask[0][0])*(cm+1));

	for (int i = 0; i < MAXC; i++)
		stat[i] = 0;
}

int jmp_next(int16_t jrow[], int x) {
	return jrow[x] == x ? x : (jrow[x] = jmp_next(jrow, jrow[x]));
}
#define FULL (~0U)
int next(int16_t jrow[], uint32_t mask[], int x) {
	int y = jmp_next(jrow, x>>5);
	uint32_t v = mask[y];
	for (int i = y == (x>>5) ? x&31 : 0; i < 32; i++) {
		if (((v>>i)&1) == 0)
			return y<<5|i;
	}
	return next(jrow, mask, (y+1)<<5);
}

void draw_line(int c, int l, int r, int16_t jrow[], uint32_t mask[]) {
	int count = 0;
	l = next(jrow, mask, l);
	while (l <= r) {
		count++;
		mask[l>>5] |= 1U<<(l&31);
		if (mask[l>>5] == FULL)
			jrow[l>>5] = jmp_next(jrow, (l>>5)+1);
		l = next(jrow, mask, l+1);
	}
	stat[c] += count;
}

void draw_circle(int c, int xc, int yc, int r) {
	int ll = max(xc-r, 0), rr = min(xc+r, n-1);
	for (int i = ll; i <= rr; i++) {
		int chord = (int) sqrt(r*r - (i-xc)*(i-xc));
		int yl = max(yc-chord, 0);
		int yr = min(yc+chord, m-1);
		draw_line(c, yl, yr, jump[i], mask[i]);
	}
}

void draw_diamond(int c, int xc, int yc, int r) {
	int ll = max(xc-r, 0), rr = min(xc+r, n-1);
	for (int i = ll; i <= rr; i++) {
		int chord = r - abs(i-xc);
		int yl = max(yc-chord, 0);
		int yr = min(yc+chord, m-1);
		draw_line(c, yl, yr, jump[i], mask[i]);
	}
}

void draw_rectangle(int c, int xc, int yc, int h, int w) {
	int ll = max(xc, 0), rr = min(xc+h-1, n-1);
	int yl = max(yc, 0);
	int yr = min(yc+w-1, m-1);
	for (int i = ll; i <= rr; i++)
		draw_line(c, yl, yr, jump[i], mask[i]);
}

void draw_triangle(int c, int xc, int yc, int w) {
	int ll = max(xc, 0), rr = min(xc+(w+1)/2-1, n-1);
	for (int i = ll; i <= rr; i++) {
		int chord = (w-1)/2 - i + xc;
		int yl = max(yc-chord, 0);
		int yr = min(yc+chord, m-1);
		draw_line(c, yl, yr, jump[i], mask[i]);
	}
}

void draw(Shape s) {
	if (s.type == 0)
		draw_circle(s.c, s.xc, s.yc, s.a);
	else if (s.type == 1)
		draw_diamond(s.c, s.xc, s.yc, s.a);
	else if (s.type == 2)
		draw_rectangle(s.c, s.xc, s.yc, s.a, s.b);
	else
		draw_triangle(s.c, s.xc, s.yc, s.a);
}

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if (p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while ((c = readchar()) < '-')	{ if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while ((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
inline int ReadStr(char *s) {
	static char c;
	while ((c = readchar()) <= ' ')	{if (c == EOF)	return 0;}
	*s = c, s++;
	while ((c = readchar()) > ' ')
		*s = c, s++;
	*s = '\0';
	return 1;
}


int main() {
	int q;
//	while (scanf("%d %d %d", &n, &m, &q) == 3) {
	while (ReadInt(&n) == 1) {
		ReadInt(&m), ReadInt(&q);
		char cmd[16];

		init(n, m);
		
		int xc, yc, r, c, l, w;
		for (int i = 0; i < q; i++) {
//			scanf("%s", cmd);
			ReadStr(cmd);
			if (cmd[0] == 'C') {
//				scanf("%d %d %d %d", &xc, &yc, &r, &c);
				ReadInt(&xc), ReadInt(&yc), ReadInt(&r), ReadInt(&c);
				shape[i] = Shape(0, c, xc, yc, r);
			} else if (cmd[0] == 'D') {
//				scanf("%d %d %d %d", &xc, &yc, &r, &c);
				ReadInt(&xc), ReadInt(&yc), ReadInt(&r), ReadInt(&c);
				shape[i] = Shape(1, c, xc, yc, r);
			} else if (cmd[0] == 'R') {
//				scanf("%d %d %d %d %d", &xc, &yc, &l, &w, &c);
				ReadInt(&xc), ReadInt(&yc), ReadInt(&l), ReadInt(&w), ReadInt(&c);
				shape[i] = Shape(2, c, xc, yc, l, w);
			} else if (cmd[0] == 'T') {
//				scanf("%d %d %d %d", &xc, &yc, &w, &c);
				ReadInt(&xc), ReadInt(&yc), ReadInt(&w), ReadInt(&c);
				shape[i] = Shape(3, c, xc, yc, w);
			}
		}

		for (int i = q-1; i >= 0; i--)
			draw(shape[i]);
		for (int i = 1; i <= 9; i++)
			printf("%d%c", stat[i], " \n"[i==9]);
	}
	return 0;
}
/*
8 8 4
Diamond 3 3 1 1
Triangle 4 4 3 2
Rectangle 1 1 2 2 3
Circle 6 6 2 4
*/
