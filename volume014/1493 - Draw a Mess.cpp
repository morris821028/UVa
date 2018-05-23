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
uint16_t jump[MAXN][MAXM];
int stat[MAXC];

void init(int n, int m) {
	for (int j = 0; j <= m; j++)
		jump[0][j] = j;
	for (int i = 1; i < n; i++)
		memcpy(jump[i], jump[0], sizeof(jump[0][0])*(m+1));
	
	for (int i = 0; i < MAXC; i++)
		stat[i] = 0;
}

int next(uint16_t jrow[], int x) {
	return jrow[x] == x ? x : (jrow[x] = next(jrow, jrow[x]));
}

void draw_line(int c, int l, int r, uint16_t jrow[]) {
	int count = 0;
	int f = next(jrow, r+1);
	l = next(jrow, l);
	while (l <= r) {
		count++;
		jrow[l] = f;
		l = next(jrow, l+1);
	}
	stat[c] += count;
}

void draw_circle(int c, int xc, int yc, int r) {
	int ll = max(xc-r, 0), rr = min(xc+r, n-1);
	for (int i = ll; i <= rr; i++) {
		int chord = (int) sqrt(r*r - (i-xc)*(i-xc));
		int yl = max(yc-chord, 0);
		int yr = min(yc+chord, m-1);
		draw_line(c, yl, yr, jump[i]);
	}
}

void draw_diamond(int c, int xc, int yc, int r) {
	int ll = max(xc-r, 0), rr = min(xc+r, n-1);
	for (int i = ll; i <= rr; i++) {
		int chord = r - abs(i-xc);
		int yl = max(yc-chord, 0);
		int yr = min(yc+chord, m-1);
		draw_line(c, yl, yr, jump[i]);
	}
}

void draw_rectangle(int c, int xc, int yc, int h, int w) {
	int ll = max(xc, 0), rr = min(xc+h-1, n-1);
	int yl = max(yc, 0);
	int yr = min(yc+w-1, m-1);
	for (int i = ll; i <= rr; i++)
		draw_line(c, yl, yr, jump[i]);
}

void draw_triangle(int c, int xc, int yc, int w) {
	int ll = max(xc, 0), rr = min(xc+(w+1)/2-1, n-1);
	for (int i = ll; i <= rr; i++) {
		int chord = (w-1)/2 - i + xc;
		int yl = max(yc-chord, 0);
		int yr = min(yc+chord, m-1);
		draw_line(c, yl, yr, jump[i]);
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

int main() {
	int q;
	while (scanf("%d %d %d", &n, &m, &q) == 3) {
		char cmd[16];

		init(n, m);
		
		int xc, yc, r, c, l, w;
		for (int i = 0; i < q; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'C') {
				scanf("%d %d %d %d", &xc, &yc, &r, &c);
				shape[i] = Shape(0, c, xc, yc, r);
			} else if (cmd[0] == 'D') {
				scanf("%d %d %d %d", &xc, &yc, &r, &c);
				shape[i] = Shape(1, c, xc, yc, r);
			} else if (cmd[0] == 'R') {
				scanf("%d %d %d %d %d", &xc, &yc, &l, &w, &c);
				shape[i] = Shape(2, c, xc, yc, l, w);
			} else if (cmd[0] == 'T') {
				scanf("%d %d %d %d", &xc, &yc, &w, &c);
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
