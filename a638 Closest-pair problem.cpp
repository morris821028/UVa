#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define oo 100000000
typedef struct {
	float x, y;
}Point;
Point D[3000000];
int cmp(const void *i, const void *j) {
	Point *x, *y;
	x = (Point *)i, y = (Point *)j;
	if(x->x != y->x)
		return x->x - y->x < 0 ? 1 : -1;
	return x->y - y->y < 0 ? 1 : -1;
}
double Min(double x, double y) {
	return x < y ? x : y;
}
double Merge(int l, int m, int r, double d) {
	double midL = D[m].x;
	int i, j;
	for(i = m; i >= l; i--) {
		if((D[i].x-midL)*(D[i].x-midL) >= d)	break;
		for(j = m+1; j <= r; j++) {
			if((D[i].x-D[j].x)*(D[i].x-D[j].x) >= d)	break;
			d = Min(d, (D[i].x-D[j].x)*(D[i].x-D[j].x)+(D[i].y-D[j].y)*(D[i].y-D[j].y));
		}
	}
	return d;
}
double ClosestPair(int l, int r, double *dis) {
	if(l < r) {
		if(l == r-1) {
			return (D[l].x-D[r].x)*(D[l].x-D[r].x) + (D[l].y-D[r].y)*(D[l].y-D[r].y);
		}
		int m = (l+r)>>1;
		*dis = Min(*dis, ClosestPair(l, m, dis));
		*dis = Min(*dis, ClosestPair(m+1, r, dis));
		*dis = Min(*dis, Merge(l, m, r, *dis));
		return *dis;
	}
	return oo;
}
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int N, i, x, y;
	ReadInt(&N);
    for(i = 0; i < N; i++) {
        ReadInt(&x), ReadInt(&y);
        D[i].x = x, D[i].y = y;
    }
    double distance = oo;
    distance = ClosestPair(0, N-1, &distance);
    distance = sqrt(distance);
    printf("%.4lf\n", distance);
    return 0;
}
