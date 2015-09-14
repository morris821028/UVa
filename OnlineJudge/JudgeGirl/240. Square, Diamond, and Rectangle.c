#include <stdio.h> 
#include <math.h>
#include <string.h>
#define eps 1e-10
typedef struct {
    int x, y;
} Pt;
Pt subtract(Pt a, Pt b) {
	Pt c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
    return c;
}
int cmp(const void * a, const void * b) {
	if ((*(Pt*)a).x != (*(Pt*)b).x)
		return (*(Pt*)a).x < (*(Pt*)b).x ? -1 : 1;
	return (*(Pt*)a).y < (*(Pt*)b).y ? -1 : 1;
}
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int monotone(int n, Pt p[], Pt ch[]) {
    qsort(p, n, sizeof(Pt), cmp);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m - 1;
}
int dist(Pt a, Pt b) {
	return (a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y);
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		Pt p[4], q[8];
		int i;
		for (i = 0; i < 4; i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		monotone(4, p, q);
		int a, b, c, d, e;
		a = dist(q[0], q[1]);
		b = dist(q[1], q[2]);
		c = dist(q[2], q[3]);
		d = dist(q[3], q[0]);
		e = dist(q[0], q[2]);
		if (a == b && b == c && c == d) {
			puts(a+b == e ? "square" : "diamond");
		} else if (a == c && b == d) {
			puts(a+b == e ? "rectangle" : "other");
		} else {
			puts("other");
		}
	}
	return 0;
}
