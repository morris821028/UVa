#include <stdio.h> 
#include <stdlib.h>
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
const char ds[4][16] = {"north", "east", "south", "west"};
int a, b, c, d, e;
int p, q, r, s, x, y, F;
int _dir(int x, int y, int a, int b) {
//	fprintf(stderr, "direction (%d*%d + %d*%d)%% 4 = %d, %s\n", a, b, c, d, (a * x + b * y)%4, ds[(a * x + b * y)%4]);
	return abs(a * x + b * y)%4;
}
int _gold(int x, int y, int c, int d, int e) {
	if (x == p && y == q)	{
//		fprintf(stderr, "collect 0 G, transporter !\n"); 
		return 0; 
	}
	if (x == r && y == s)	{
//		fprintf(stderr, "collect 0 G, transporter !\n"); 
		return 0; 
	}
//	fprintf(stderr, "collect (%d*%d + %d*%d) %% %d = %d G\n", c, x, d, y, e, (c * x + d * y)%e);
	return abs(c * x + d * y)%e;
}
int _sim() {
	int dir = _dir(x, y, a, b);
//	fprintf(stderr, "(%d, %d) %s (%d, %d)\n", x, y, ds[dir], x+dx[dir], y+dy[dir]);
	x += dx[dir], y += dy[dir];
	if (x == p && y == q) {
		x = r, y = s;
//		fprintf(stderr, "transport (%d, %d) to (%d, %d)\n", p, q, r, s);
	} else if (x == r && y == s) {
		x = p, y = q;
//		fprintf(stderr, "transport (%d, %d) to (%d, %d)\n", r, s, p, q);
	}
	return _gold(x, y, c, d, e);
}
int main() {
	while (scanf("%d %d %d %d %d", &a, &b, &c, &d, &e) == 5) {
		scanf("%d %d %d %d", &p, &q, &r, &s);
		scanf("%d %d %d", &x, &y, &F);
		
		int ret = _gold(x, y, c, d, e);
		for (int i = 0; i < F; i++)
			ret += _sim();
		printf("%d\n", ret);
		printf("%d %d\n", x, y);
	}
	return 0;
}
/*
1 3 5 7 9
1 2 3 4
1 1 6
*/


